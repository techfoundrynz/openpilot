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

    # Properties for smooth transitions and state stability
    self.current_priority = 0
    self.last_anim_change_time = 0.0
    self.last_left_blinker_time = 0.0
    self.last_right_blinker_time = 0.0

  def update_animation(self):
    now = time.monotonic()

    if not ui_state.sm.valid["carState"]:
      if self.current_anim != 0:
        self.current_anim = 0
        self.num_frames = 6
        self.frame = 0
        self.last_anim_change_time = now
      self.current_priority = 0
      return

    cs = ui_state.sm["carState"]
    model = ui_state.sm["modelV2"] if "modelV2" in ui_state.sm.services and ui_state.sm.seen["modelV2"] else None

    override_predicted = False
    turn_left_predicted = False
    turn_right_predicted = False
    system_lagging = False
    lead_braking_panic = False

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

      if len(model.leadsV3) > 0 and model.leadsV3[0].prob > 0.7 and len(model.leadsV3[0].x) > 0:
        if len(model.leadsV3[0].a) > 0 and model.leadsV3[0].a[0] < -3.0:
          lead_braking_panic = True

    # Blinker filter (1.5 seconds cooldown)
    if cs.leftBlinker or turn_left_predicted:
      self.last_left_blinker_time = now
    if cs.rightBlinker or turn_right_predicted:
      self.last_right_blinker_time = now

    left_blinker_active = (now - self.last_left_blinker_time < 1.5)
    right_blinker_active = (now - self.last_right_blinker_time < 1.5)

    # Determine desired animation state and priority
    desired_row = 0
    desired_frames = 6
    desired_priority = 0

    # High-Priority States (Priority 3)
    if system_lagging:
      desired_row, desired_frames, desired_priority = 6, 8, 3
    elif (model is not None and model.meta.hardBrakePredicted) or lead_braking_panic:
      desired_row, desired_frames, desired_priority = 5, 8, 3
    elif override_predicted and ui_state.status != UIStatus.DISENGAGED:
      desired_row, desired_frames, desired_priority = 3, 4, 3
    elif ui_state.status == UIStatus.OVERRIDE:
      desired_row, desired_frames, desired_priority = 5, 8, 3
    # Medium-Priority States (Priority 2)
    elif left_blinker_active:
      desired_row, desired_frames, desired_priority = 2, 8, 2
    elif right_blinker_active:
      desired_row, desired_frames, desired_priority = 1, 8, 2
    # Low-Priority States (Priority 1)
    elif ui_state.status != UIStatus.DISENGAGED:
      if cs.vEgo < 0.1:
        desired_row, desired_frames, desired_priority = 3, 4, 1
      elif model is not None and len(model.leadsV3) > 0 and model.leadsV3[0].prob > 0.7 and len(model.leadsV3[0].x) > 0 and model.leadsV3[0].x[0] < 40.0:
        desired_row, desired_frames, desired_priority = 7, 6, 1
      else:
        desired_row, desired_frames, desired_priority = 4, 5, 1
    # Lowest-Priority States (Priority 0)
    else:
      if cs.vEgo >= 0.1:
        desired_row, desired_frames, desired_priority = 7, 6, 1  # Manual driving is priority 1
      else:
        if model is not None and model.meta.engagedProb > 0.4:
          desired_row, desired_frames, desired_priority = 0, 6, 0
        else:
          desired_row, desired_frames, desired_priority = 6, 8, 0

    # Apply priority-based hysteresis and transition cooldown
    if (desired_priority > self.current_priority) or (now - self.last_anim_change_time >= 1.0) or (self.current_anim == desired_row):
      if self.current_anim != desired_row:
        self.current_anim = desired_row
        self.num_frames = desired_frames
        self.frame = 0
        self.last_anim_change_time = now
      self.current_priority = desired_priority

  def _set_anim(self, anim_row: int, num_frames: int):
    if self.current_anim != anim_row:
      self.current_anim = anim_row
      self.num_frames = num_frames
      self.frame = 0
      self.last_anim_change_time = time.monotonic()

  def _render(self, _):
    self.update_animation()

    cs = ui_state.sm["carState"]
    model = ui_state.sm["modelV2"] if "modelV2" in ui_state.sm.services and ui_state.sm.seen["modelV2"] else None

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
        # Map std_val to opacity:
        # std_val <= 0.3 -> opacity 1.0 (fully opaque)
        # std_val >= 0.8 -> opacity 0.4 (minimum opacity, so he's still visible)
        if std_val <= 0.3:
          opacity_factor = 1.0
        elif std_val >= 0.8:
          opacity_factor = 0.4
        else:
          opacity_factor = 1.0 - 0.6 * ((std_val - 0.3) / 0.5)
        alpha = max(0, min(255, int(255 * opacity_factor)))

      # 3. Lane Centering Drift (50 pixels per meter)
      if len(model.position.y) > 0:
        x_offset = float(-model.position.y[0] * 50.0)

      # 4. Lead Car Approaching
      if len(model.leadsV3) > 0 and model.leadsV3[0].prob > 0.7 and len(model.leadsV3[0].x) > 0:
        lead_dist = model.leadsV3[0].x[0]
        if lead_dist < 20.0:
          scale_multiplier = 1.0 + (20.0 - lead_dist) / 40.0 # Grow slightly when close

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
