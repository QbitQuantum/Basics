void
ObjectIcon::draw(DrawingContext& context, Vector pos) {
  context.draw_surface_part(surface, Rectf(Vector(0,0), surface->get_size()),
                            Rectf(pos + offset, pos + Vector(32,32) - offset), LAYER_GUI - 9);
}