bool CalibrationArea::on_expose_event(GdkEventExpose *event)
{
    // check that screensize did not change
    if (display_width != get_width() ||
         display_height != get_height()) {
        set_display_size(get_width(), get_height());
    }

    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
        cr->save();

        cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
        cr->clip();

        // Print the text
        cr->set_font_size(font_size);
        double text_height = -1;
        double text_width = -1;
        Cairo::TextExtents extent;
        for (int i = 0; i != help_lines; i++) {
            cr->get_text_extents(help_text[i], extent);
            text_width = std::max(text_width, extent.width);
            text_height = std::max(text_height, extent.height);
        }
        text_height += 2;

        double x = (display_width - text_width) / 2;
        double y = (display_height - text_height) / 2 - 60;
        cr->set_line_width(2);
        cr->rectangle(x - 10, y - (help_lines*text_height) - 10,
                text_width + 20, (help_lines*text_height) + 20);

        // Print help lines
        y -= 3;
        for (int i = help_lines-1; i != -1; i--) {
            cr->get_text_extents(help_text[i], extent);
            cr->move_to(x + (text_width-extent.width)/2, y);
            cr->show_text(help_text[i]);
            y -= text_height;
        }
        cr->stroke();

        // Draw the points
        for (int i = 0; i <= calibrator->get_numclicks(); i++) {
            // set color: already clicked or not
            if (i < calibrator->get_numclicks())
                cr->set_source_rgb(1.0, 1.0, 1.0);
            else
                cr->set_source_rgb(0.8, 0.0, 0.0);

            cr->set_line_width(1);
            cr->move_to(X[i] - cross_lines, Y[i]);
            cr->rel_line_to(cross_lines*2, 0);
            cr->move_to(X[i], Y[i] - cross_lines);
            cr->rel_line_to(0, cross_lines*2);
            cr->stroke();

            cr->arc(X[i], Y[i], cross_circle, 0.0, 2.0 * M_PI);
            cr->stroke();
        }

        // Draw the clock background
        cr->arc(display_width/2, display_height/2, clock_radius/2, 0.0, 2.0 * M_PI);
        cr->set_source_rgb(0.5, 0.5, 0.5);
        cr->fill_preserve();
        cr->stroke();

        cr->set_line_width(clock_line_width);
        cr->arc(display_width/2, display_height/2, (clock_radius - clock_line_width)/2,
             3/2.0*M_PI, (3/2.0*M_PI) + ((double)time_elapsed/(double)max_time) * 2*M_PI);
        cr->set_source_rgb(0.0, 0.0, 0.0);
        cr->stroke();


        // Draw the message (if any)
        if (message != NULL) {
            // Frame the message
            cr->set_font_size(font_size);
            Cairo::TextExtents extent;
            cr->get_text_extents(this->message, extent);
            text_width = extent.width;
            text_height = extent.height;

            x = (display_width - text_width) / 2;
            y = (display_height - text_height + clock_radius) / 2 + 60;
            cr->set_line_width(2);
            cr->rectangle(x - 10, y - text_height - 10,
                    text_width + 20, text_height + 25);

            // Print the message
            cr->move_to(x, y);
            cr->show_text(this->message);
            cr->stroke();
        }

        cr->restore();
    }

    return true;
}