bool CircuitWidget::on_expose_event(GdkEventExpose* event)
{

    (void)event; // placate compiler..
    Glib::RefPtr<Gdk::Window> window = get_window();
    if(window) {
        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        double xc = width/2.0;
        double yc = height/2.0;

        Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
        circuitDrawer.renderCairo(cr->cobj());
        cr->rectangle(event->area.x, event->area.y,
                      event->area.width, event->area.height);
        cr->clip();
        cr->rectangle (0, 0, width, height);
        cr->set_source_rgb (1,1,1);
        cr->fill ();
        cr->translate (xc-ext.width/2.0-cx*scale, yc-ext.height/2.0-cy*scale);
        if (circuit) {
            rects = circuitDrawer.draw(*circuit, drawarch, drawparallel, ext, wirestart, wireend, scale, selections, ft_default, wirelabels);
            generate_layout_rects ();
        }
    }

    return true;
}