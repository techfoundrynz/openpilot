import time
import pyray as rl
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.lib.application import gui_app

class TamagotchiWidget(Widget):
  def __init__(self, scale=1.0):
    super().__init__()
    
    self.frame_width = 1536 / 8
    self.frame_height = 1872 / 9
    self.num_frames = 6 # idle frames
    self.fps = 10
    
    self.set_rect(rl.Rectangle(0, 0, self.frame_width * scale, self.frame_height * scale))
    self._texture = gui_app.texture("pingu_spritesheet.png")
    
    self.frame = 0
    self.last_update = time.monotonic()
    
  def _render(self, _):
    now = time.monotonic()
    if now - self.last_update > 1.0 / self.fps:
      self.frame = int((self.frame + 1) % self.num_frames)
      self.last_update = now
      
    src_rect = rl.Rectangle(self.frame * self.frame_width, 0, self.frame_width, self.frame_height)
    dst_rect = rl.Rectangle(self.rect.x, self.rect.y, self.rect.width, self.rect.height)
    rl.draw_texture_pro(self._texture, src_rect, dst_rect, rl.Vector2(0, 0), 0.0, rl.WHITE)
