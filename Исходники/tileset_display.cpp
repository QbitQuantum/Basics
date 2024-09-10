bool level_editor::tileset_display::on_expose_event(GdkEventExpose* event) {
  Glib::RefPtr<Gdk::Window> window = get_window();

  if (!window || !m_surface)
    return true;

  Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
  cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
  cr->clip();

  cr->set_source(m_surface, 0, 0);
  cr->paint();

  // Show selection rectangle when we are selecting
  if (m_selecting
      || ((m_select_x != m_select_end_x || m_select_y != m_select_end_y)
          && m_preferences.sticky_tile_selection)) {
    const int x = std::min(m_select_x, m_select_end_x) * m_tile_width;
    const int y = std::min(m_select_y, m_select_end_y) * m_tile_height;

    const int w = (std::abs(m_select_x - m_select_end_x))
                    * m_tile_width;
    const int h = (std::abs(m_select_y - m_select_end_y))
                    * m_tile_height;

    cr->save();
      cr->rectangle(x, y, w, h);
      // TODO: move selection color somewhere else (preferences?)
      cr->set_source_rgb(0.7, 1, 1);
      if (m_preferences.selection_background) {
        cr->stroke_preserve();
        cr->set_source_rgba(0.7, 1, 0, 0.2);
        cr->fill();
      } else {
        cr->stroke();
      }
    cr->restore();
  }

  return true;
}