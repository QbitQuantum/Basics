bool CompVis::on_expose_event(GdkEventExpose* event) {
    Glib::RefPtr<Gdk::Window> window = get_window();
    Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
            
    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
        
    // clip to the area indicated by the expose event so that we only redraw
    // the portion of the window that needs to be redrawn
    cr->rectangle(event->area.x, event->area.y,
    event->area.width, event->area.height);
    cr->clip();
           
    rms_dB = 20*log10(rms);
    thresh_fraction = (threshold -  p_ports[p_threshold].min)/threshold_range;
    rms_dB_fraction = (rms_dB - p_ports[p_threshold].min)/threshold_range;

    // Draw the graph
    cr->set_source_rgb(0.5,0.1,0.1);
    cr->set_line_width(2);
    cr->move_to(0,height);

    if (rms_dB <= threshold) {
        cr->line_to(rms_dB_fraction*width, height-rms_dB_fraction*height);
        cr->line_to(rms_dB_fraction*width, height);
        cr->line_to(0,height);
    } else {
        cr->line_to(thresh_fraction*width, height-thresh_fraction*height);
        cr->line_to(rms_dB_fraction*width, height-(thresh_fraction*height + height*(rms_dB_fraction-thresh_fraction)/ratio));
        cr->line_to(rms_dB_fraction*width, height);
        cr->line_to(0,height);
    }
    cr->fill();

    // draw the compression curve:
    cr->set_source_rgb(0.1,0.1,0.1);
    cr->move_to(0, height);
    cr->line_to(thresh_fraction*width, height-thresh_fraction*height);
    cr->line_to(width, height-(thresh_fraction*height + height*(1-thresh_fraction)/ratio));
    cr->stroke();

    // Draw the gain
    cr->set_source_rgb(0.1,0.8,0.1);
    cr->rectangle(0,(float)height - (float)height*gain, 10, height);
    cr->fill();
    return true;
}