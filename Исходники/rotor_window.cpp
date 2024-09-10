void enigma_rotor_window::draw(Cairo::RefPtr<Cairo::Context> cr)
{
    vector<double> dashes;
    // Pattern used to draw a dashed line (15 pixels of line followed by 15 "empty" pixels)
    dashes.push_back(15.0);
    dashes.push_back(15.0);
    
    if (has_ellipse)
    {
        cr->save();
        
            // Draw background ellipse
            cr->set_source_rgb(bkg_r, bkg_g, bkg_b);
            draw_ellipse(cr, x, y, ellipse_width, ellipse_height);
            cr->fill();
            // Draw black border of background ellipse
            cr->set_source_rgb(BLACK);
            cr->set_line_width(1.2);
            draw_ellipse(cr, x, y, ellipse_width, ellipse_height);
            cr->stroke();
        
        cr->restore();
    }
    
    cr->save();  
    
        // Draw a line of width rotor_rim_width in the dash background colour
        cr->set_line_width(rotor_rim_width);
        cr->set_source_rgb(dash_bkg_r, dash_bkg_g, dash_bkg_b);
        cr->move_to(x + window_size, y - (2 * window_size));
        cr->line_to(x + window_size, y + (2 * window_size));
        cr->stroke();
        
        // Draw a dashed line in the dash colour inside the previously drawn line
        // This creates the impression of "notches" on the handle/rim
        cr->set_source_rgb(dash_r, dash_g, dash_b);
        cr->set_dash(dashes, ((wheel_pos - 'A') & 1) * 15); // modifying the offset creates illusion of movement
        
        cr->move_to(x + window_size, y - (2 * window_size));
        cr->line_to(x + window_size, y + (2 * window_size));
        cr->stroke();
        
        // Draw border around handle/rim
        cr->set_line_width(2.0);
        cr->unset_dash();
        cr->set_source_rgb(DARK_GREY);
        cr->rectangle(x + padded_size, y - (2 * window_size), rotor_rim_width, (4 * window_size));
        cr->stroke();
    
    cr->restore();

    draw_wheel_pos(cr, wheel_pos);
    
    if (has_ellipse)
    {
        // Draw screws
        upper->draw(cr);
        lower->draw(cr);    
    }
}