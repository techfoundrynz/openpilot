import time
import pyray as rl
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.lib.application import gui_app
from openpilot.selfdrive.ui.ui_state import ui_state, UIStatus

class TamagotchiWidget(Widget):
  def __init__(self, scale=1.0):
    super().__init__()

    self.frame_width = 1536 / 8
    self.frame_height = 1872 / 9

    self.set_rect(rl.Rectangle(0, 0, self.frame_width * scale, self.frame_height * scale))
    self._texture = gui_app.texture("pingu_spritesheet.png")

    self.frame = 0
    self.last_update = time.monotonic()
    self.fps = 6

    self.current_anim = 0
    self.num_frames = 6

  def update_animation(self):
    if not ui_state.sm.valid["carState"]:
      self._set_anim(0, 6)
      return

    cs = ui_state.sm["carState"]
    model = ui_state.sm.get("modelV2", None)

    override_predicted = False
    turn_left_predicted = False
    turn_right_predicted = False
    system_lagging = False

    if model is not None:
      if len(model.meta.disengagePredictions.steerOverrideProbs) > 0:
        override_predicted = override_predicted or model.meta.disengagePredictions.steerOverrideProbs[0] > 0.5
      if len(model.meta.disengagePredictions.brakeDisengageProbs) > 0:
        override_predicted = override_predicted or model.meta.disengagePredictions.brakeDisengageProbs[0] > 0.5

      # Map ALC and sharp lateral acceleration to Left/Right looking sprites
      lc_state = str(model.meta.laneChangeState)
      lc_dir = str(model.meta.laneChangeDirection)
      if lc_state != 'off':
        if lc_dir == 'left': turn_left_predicted = True
        elif lc_dir == 'right': turn_right_predicted = True

      if len(model.acceleration.y) > 0:
        # High lateral acceleration (cornering) -> Look into the turn!
        if model.acceleration.y[0] > 2.0: turn_left_predicted = True
        elif model.acceleration.y[0] < -2.0: turn_right_predicted = True

      if model.frameDropPerc > 20.0:
        system_lagging = True

    # High-Priority States
    if system_lagging:
      self._set_anim(6, 8) # Passes out / Sleeps if the camera drops too many vision frames
    elif model is not None and model.meta.hardBrakePredicted:
      self._set_anim(5, 8) # Surprised / Afraid animation for hard brake!
    elif override_predicted and ui_state.status != UIStatus.DISENGAGED:
      self._set_anim(3, 4) # Waves goodbye in the exact moment before a predicted driver override!
    elif ui_state.status == UIStatus.OVERRIDE:
      self._set_anim(5, 8)
    elif cs.leftBlinker or turn_left_predicted:
      self._set_anim(2, 8)
    elif cs.rightBlinker or turn_right_predicted:
      self._set_anim(1, 8)
    elif ui_state.status != UIStatus.DISENGAGED:
      if cs.vEgo < 0.1:
        self._set_anim(3, 4) # Waving when engaged but stopped
      elif model is not None and len(model.leadsV3) > 0 and model.leadsV3[0].prob > 0.7 and len(model.leadsV3[0].x) > 0 and model.leadsV3[0].x[0] < 40.0:
        self._set_anim(7, 6) # Running to keep up with a lead car!
      else:
        self._set_anim(4, 5) # Jumping when engaged and moving freely
    else:
      if cs.vEgo >= 0.1:
        self._set_anim(7, 6) # Running when moving manually
      else:
        if model is not None and model.meta.engagedProb > 0.4:
          self._set_anim(0, 6) # Wake up (Idle) in anticipation when AI predicts user is engaging
        else:
          self._set_anim(6, 8) # Sleeping when stopped manually

  def _set_anim(self, anim_row: int, num_frames: int):
    if self.current_anim != anim_row:
      self.current_anim = anim_row
      self.num_frames = num_frames
      self.frame = 0

  def _render(self, _):
    self.update_animation()

    cs = ui_state.sm["carState"]
    model = ui_state.sm.get("modelV2", None)

    # 1. Dynamic FPS based on speed
    self.fps = max(4, min(24, int(cs.vEgo * 0.8)))

    alpha = 255
    scale_multiplier = 1.0
    rotation = 0.0
    x_offset = 0.0

    if ui_state.sm.valid["carState"] and model is not None:
      # 2. AI Confidence Fading
      if len(model.laneLineStds) >= 3:
        std_val = (model.laneLineStds[1] + model.laneLineStds[2]) / 2.0
        opacity_factor = max(0.2, 1.0 - (std_val * 4.0))
        alpha = max(0, min(255, int(255 * opacity_factor)))

      # 3. Lane Centering Drift (50 pixels per meter)
      if len(model.position.y) > 0:
        x_offset = float(-model.position.y[0] * 50.0)

      # 4. Lead Car Approaching & Hard Braking Panic
      if len(model.leadsV3) > 0 and model.leadsV3[0].prob > 0.7 and len(model.leadsV3[0].x) > 0:
        lead_dist = model.leadsV3[0].x[0]
        if lead_dist < 20.0:
          scale_multiplier = 1.0 + (20.0 - lead_dist) / 40.0 # Grow slightly when close
        if len(model.leadsV3[0].a) > 0 and model.leadsV3[0].a[0] < -3.0:
           self._set_anim(5, 8) # React (Surprised) to lead car slamming brakes

      # 5. Road Pitch (Rotation)
      if len(model.position.z) >= 10 and len(model.position.x) >= 10:
        import math
        dz = model.position.z[9] - model.position.z[0]
        dx = model.position.x[9] - model.position.x[0]
        if dx > 0.1:
          rotation = math.degrees(math.atan2(dz, dx)) * 2.5 # Exaggerate the pitch

    now = time.monotonic()
    if now - self.last_update > 1.0 / self.fps:
      self.frame = int((self.frame + 1) % self.num_frames)
      self.last_update = now

    src_rect = rl.Rectangle(self.frame * self.frame_width, self.current_anim * self.frame_height, self.frame_width, self.frame_height)
    
    current_width = self.rect.width * scale_multiplier
    current_height = self.rect.height * scale_multiplier
    
    # Adjust dst_rect to account for PyRay origin parameter (which creates the rotational center)
    origin_x = current_width / 2.0
    origin_y = current_height / 2.0
    dst_x = self.rect.x + x_offset + origin_x
    dst_y = self.rect.y + (self.rect.height - current_height) + origin_y
    dst_rect = rl.Rectangle(dst_x, dst_y, current_width, current_height)
    
    color = rl.Color(255, 255, 255, alpha)

    rl.draw_texture_pro(self._texture, src_rect, dst_rect, rl.Vector2(origin_x, origin_y), rotation, color)
