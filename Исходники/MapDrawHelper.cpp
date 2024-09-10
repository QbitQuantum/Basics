void 
MapDrawHelper::draw_search_point_vector(Canvas& the_canvas, 
                                        const SearchPointVector& points) 
{
  const size_t size = points.size();
  if (size<3) {
    return;
  }

  MapCanvas map_canvas(the_canvas, m_proj);
  POINT screen[size];
  map_canvas.project(points, screen);

  if (!map_canvas.visible(screen, size))
    return;

  the_canvas.polygon(&screen[0], size);
  if (m_use_stencil) {
    m_stencil.polygon(&screen[0], size);
  }
}