bool
ButtonWidget::on_expose_event(GdkEventExpose* event)
{
  Gtk::DrawingArea::on_expose_event(event);
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
    {
      Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

      int w  = get_allocation().get_width()  - 10;
      int h  = get_allocation().get_height() - 10;

      cr->set_source_rgb(0.0, 0.0, 0.0);
      cr->set_line_width(1.0);
      cr->translate(5, 5);
      cr->rectangle(0, 0, w, h);
      
      if (down)
        cr->fill_preserve();

      cr->stroke();

      if (down)
        cr->set_source_rgb(1.0, 1.0, 1.0);

      // FIXME: There are better ways to center text
      if (name.size() == 2)
        cr->move_to(w/2-6, h/2+3);
      else
        cr->move_to(w/2-4, h/2+3);
      cr->show_text(name);
    }

  return true;
}