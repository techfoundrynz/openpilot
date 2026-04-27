"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import os
import sys
import subprocess
from openpilot.common.basedir import BASEDIR
from openpilot.selfdrive.ui.sunnypilot.mici.layouts.vehicle_sub_layouts.brands.base import BrandSettingsMici
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr
from openpilot.selfdrive.ui.mici.widgets.button import BigButton
from openpilot.selfdrive.ui.mici.widgets.dialog import BigConfirmationDialog, BigDialog

import struct
import threading
from datetime import date
from enum import IntEnum

from opendbc.car.structs import CarParams
from opendbc.car.uds import UdsClient, MessageTimeoutError, NegativeResponseError, SESSION_TYPE, DATA_IDENTIFIER_TYPE, ACCESS_TYPE
from panda import Panda

class VOLKSWAGEN_DATA_IDENTIFIER_TYPE(IntEnum):
  CODING = 0x0600

class ACCESS_TYPE_LEVEL_1(IntEnum):
  REQUEST_SEED = ACCESS_TYPE.REQUEST_SEED + 2
  SEND_KEY = ACCESS_TYPE.SEND_KEY + 2

MQB_EPS_CAN_ADDR = 0x712
RX_OFFSET = 0x6a

class VolkswagenSettingsMici(BrandSettingsMici):
  def __init__(self):
    super().__init__()

    self.init_mqb_config = BigButton(
      tr("Initialize VW MQB config")
    )
    self.init_mqb_config.set_click_callback(self._on_init_mqb_config)

    self.items = [
      self.init_mqb_config,
    ]

  def _run_config(self, action="enable"):
    try:
      # Temporarily kill pandad so we can grab the exclusive Panda USB lock. 
      # The system manager will automatically restart pandad, but pandad will gracefully 
      # wait in a connect loop until our Panda() object goes out of scope and releases the lock.
      try:
        subprocess.call(["pkill", "-9", "-f", "pandad"])
      except Exception:
        pass
        
      import time
      time.sleep(0.5)

      panda = Panda()
      panda.set_safety_mode(CarParams.SafetyModel.elm327)
      uds_client = UdsClient(panda, MQB_EPS_CAN_ADDR, MQB_EPS_CAN_ADDR + RX_OFFSET, 1, timeout=0.2)

      try:
        uds_client.diagnostic_session_control(SESSION_TYPE.EXTENDED_DIAGNOSTIC)
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Error"), tr("Timeout opening session with EPS.")))
        return

      try:
        odx_file = uds_client.read_data_by_identifier(DATA_IDENTIFIER_TYPE.ODX_FILE).decode("utf-8").rstrip('\x00')
        current_coding = uds_client.read_data_by_identifier(VOLKSWAGEN_DATA_IDENTIFIER_TYPE.CODING)
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Error"), tr("Timeout fetching data from EPS.")))
        return

      coding_length = len(current_coding)
      current_coding_array = struct.unpack(f"!{coding_length}B", current_coding)

      if odx_file in ("EV_SteerAssisMQB", "EV_SteerAssisMNB"):
        coding_variant, coding_byte, coding_bit = "ZFLS", 0, 4
      elif odx_file in ("EV_SteerAssisVWBSMQBA", "EV_SteerAssisVWBSMQBGen2"):
        coding_variant, coding_byte, coding_bit = "APA", 3, 0
      else:
        gui_app.push_widget(BigDialog(tr("Unsupported"), tr("Configuration changes not yet supported on this EPS (Variant: %s)!") % odx_file))
        return

      if action == "enable":
        new_byte = current_coding_array[coding_byte] | (1 << coding_bit)
      else:
        new_byte = current_coding_array[coding_byte] & ~(1 << coding_bit)
      new_coding = current_coding[0:coding_byte] + new_byte.to_bytes(1, "little") + current_coding[coding_byte+1:]

      try:
        seed = uds_client.security_access(ACCESS_TYPE_LEVEL_1.REQUEST_SEED)
        key = struct.unpack("!I", seed)[0] + 28183
        uds_client.security_access(ACCESS_TYPE_LEVEL_1.SEND_KEY, struct.pack("!I", key))
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Security Failed"), tr("Security access failed! Ensure the hood is fully open.")))
        return

      try:
        current_date = date.today()
        formatted_date = current_date.strftime('%y-%m-%d')
        year, month, day = (int(part) for part in formatted_date.split('-'))
        prog_date = bytes([year, month, day])
        uds_client.write_data_by_identifier(DATA_IDENTIFIER_TYPE.PROGRAMMING_DATE, prog_date)
        tester_num = uds_client.read_data_by_identifier(DATA_IDENTIFIER_TYPE.CALIBRATION_REPAIR_SHOP_CODE_OR_CALIBRATION_EQUIPMENT_SERIAL_NUMBER)
        uds_client.write_data_by_identifier(DATA_IDENTIFIER_TYPE.REPAIR_SHOP_CODE_OR_TESTER_SERIAL_NUMBER, tester_num)
        uds_client.write_data_by_identifier(VOLKSWAGEN_DATA_IDENTIFIER_TYPE.CODING, new_coding)
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Write Failed"), tr("Writing new configuration failed.")))
        return

      try:
        readback = uds_client.read_data_by_identifier(VOLKSWAGEN_DATA_IDENTIFIER_TYPE.CODING)
        if readback == new_coding:
          gui_app.push_widget(BigDialog(tr("Success"), tr("EPS configuration successfully verified and updated.\n\nCRITICAL: You MUST cycle the ignition fully off and back on for changes to take effect.")))
        else:
          gui_app.push_widget(BigDialog(tr("Validation Error"), tr("Coding mismatch after writing. Configuration may have failed.")))
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Readback Failed"), tr("Failed to read back updated coding for validation! Cycle ignition and try again.")))
        return

    except Exception as e:
      gui_app.push_widget(BigDialog(tr("Error"), tr(f"Unexpected error during initialization: {e}")))

  def _push_confirmation_sequence(self):
    def confirm_step_3():
      threading.Thread(target=self._run_config, args=("enable",)).start()

    def confirm_step_2():
      gui_app.push_widget(BigConfirmationDialog(
        tr("Step 3/3: Is the Hood OPEN?\n(Required to bypass the diagnostic firewall)"),
        None,
        confirm_callback=confirm_step_3
      ))

    def confirm_step_1():
      gui_app.push_widget(BigConfirmationDialog(
        tr("Step 2/3: Is the Engine OFF?"),
        None,
        confirm_callback=confirm_step_2
      ))

    gui_app.push_widget(BigConfirmationDialog(
      tr("Initialize VW MQB config?\nStep 1/3: Is the Ignition ON?"),
      None,
      confirm_callback=confirm_step_1
    ))

  def _check_is_enabled(self):
    try:
      try:
        subprocess.call(["pkill", "-9", "-f", "pandad"])
      except Exception:
        pass
        
      import time
      time.sleep(0.5)

      panda = Panda()
      panda.set_safety_mode(CarParams.SafetyModel.elm327)
      uds_client = UdsClient(panda, MQB_EPS_CAN_ADDR, MQB_EPS_CAN_ADDR + RX_OFFSET, 1, timeout=0.2)

      try:
        uds_client.diagnostic_session_control(SESSION_TYPE.EXTENDED_DIAGNOSTIC)
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Error"), tr("Timeout opening session with EPS. Ensure ignition is ON.")))
        return

      try:
        odx_file = uds_client.read_data_by_identifier(DATA_IDENTIFIER_TYPE.ODX_FILE).decode("utf-8").rstrip('\x00')
        current_coding = uds_client.read_data_by_identifier(VOLKSWAGEN_DATA_IDENTIFIER_TYPE.CODING)
      except (NegativeResponseError, MessageTimeoutError):
        gui_app.push_widget(BigDialog(tr("Error"), tr("Timeout fetching data from EPS.")))
        return

      coding_length = len(current_coding)
      current_coding_array = struct.unpack(f"!{coding_length}B", current_coding)

      if odx_file in ("EV_SteerAssisMQB", "EV_SteerAssisMNB"):
        coding_variant, coding_byte, coding_bit = "ZFLS", 0, 4
      elif odx_file in ("EV_SteerAssisVWBSMQBA", "EV_SteerAssisVWBSMQBGen2"):
        coding_variant, coding_byte, coding_bit = "APA", 3, 0
      else:
        gui_app.push_widget(BigDialog(tr("Unsupported"), tr("Configuration changes not yet supported on this EPS (Variant: %s)!") % odx_file))
        return

      hca_enabled = (current_coding_array[coding_byte] & (1 << coding_bit) != 0)
      if hca_enabled:
        gui_app.push_widget(BigDialog(tr("Information"), tr("Heading Control Assist (Lane Assist) is already enabled on this vehicle. No changes are required.")))
        return
        
    except Exception as e:
      gui_app.push_widget(BigDialog(tr("Error"), tr(f"Unexpected error during pre-flight check: {e}")))
      return
      
    # Pre-flight check passed and configuration is not currently enabled.
    self._push_confirmation_sequence()

  def _on_init_mqb_config(self):
    threading.Thread(target=self._check_is_enabled).start()

  def update_settings(self):
    is_mqb = False
    platform_name = None

    bundle = ui_state.params.get("CarPlatformBundle")
    if bundle:
      platform_name = bundle.get("name")
    elif ui_state.CP is not None and ui_state.CP.carFingerprint != "MOCK":
      platform_name = ui_state.CP.carFingerprint

    if platform_name:
      try:
        from opendbc.car.volkswagen.values import CAR, VolkswagenMQBPlatformConfig
        # CAR(platform_name) will return the enum member if valid
        config = CAR(platform_name).config
        # PQ and MLB configurations are subclasses or separate classes
        # By ensuring exact type match, we verify it is strictly the MQB platform
        is_mqb = type(config) is VolkswagenMQBPlatformConfig
      except Exception:
        pass

    # Hide the button for non-MQB platforms, and disable it if engaged
    self.init_mqb_config.set_visible(is_mqb)
    self.init_mqb_config.set_enabled(not ui_state.engaged)
