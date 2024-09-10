void
BicyclePlatform::draw(DrawingContext& context)
{
  if (g_debug.show_collision_rects) {
    context.color().draw_filled_rect(Rectf::from_center(m_center, Sizef(16, 16)), Color::MAGENTA, LAYER_OBJECTS);
  }
}