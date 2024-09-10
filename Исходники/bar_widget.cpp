// ----------------------------------------------------------------------------
// -- Function    : draw_bar(cr)
// --
// -- Takes       : cr = point to a cairo reference
// --
// -- Purpose     : Assumes value is already between 1 and 0!  Draws the bar
//                  on the provided cairo reference.
void BarWidget::draw_bar(Cairo::RefPtr<Cairo::Context> cr)
{
    // Get our bar coords
    Size size = get_avail_rect();
    Size* s = &size;

    // Draw the bg first
    cr->set_line_width(bar_bg_border_width);
    cr->rectangle(s->x, s->y, s->width, s->height);

    // -- bg border
    if (draw_bar_bg_border)
    {
        bar_bg_border_color->set_source(cr);
        cr->stroke_preserve();
    }
    // -- bg
    if (draw_bar_bg)
    {
        bar_bg_color->set_source(cr);
        cr->fill_preserve();
    }

    // Clear the path
    cr->begin_new_path();

    // -- Now we're drawing the value bar
    // Modify the size by our value / percent
    // If we're horz, modify the width.
    // If we're vert, modify the height.
    if (vertical)
        s->height = s->height * m_value;
    else
        s->width = s->width * m_value;

    // New path, draw!
    cr->set_line_width(bar_border_width);
    cr->rectangle(s->x, s->y, s->width, s->height);

    // -- bar border
    if (draw_bar_border)
    {
        bar_border_color->set_source(cr);
        cr->stroke_preserve();
    }

    // -- Draw the bar
    bar_color->set_source(cr);
    cr->fill();

    // clean up
    cr->begin_new_path();
    s = nullptr;
}