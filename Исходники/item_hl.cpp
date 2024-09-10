void
ItemHorizontalLine::draw(DrawingContext& context, const Vector& pos, int menu_width, bool active) {
  // TODO
  /* Draw a horizontal line with a little 3d effect */
  context.color().draw_filled_rect(Rectf(Vector(pos.x, pos.y - 6.0f),
                                         Sizef(static_cast<float>(menu_width), 4.0f)),
                                   Color(0.6f, 0.7f, 1.0f, 1.0f), LAYER_GUI);
  context.color().draw_filled_rect(Rectf(Vector(pos.x, pos.y - 6.0f),
                                         Sizef(static_cast<float>(menu_width), 2.0f)),
                                   Color(1.0f, 1.0f, 1.0f, 1.0f), LAYER_GUI);
}