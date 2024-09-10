void RegionChooser::draw_keyboard(const Cairo::RefPtr<Cairo::Context>& cr,
                                  int clip_low, int clip_high) {
    const int h = KEYBOARD_HEIGHT;
    const int w = get_width() - 1;
    const int bh = int(h * 0.55);

    Gdk::Cairo::set_source_rgba(cr, black);
    cr->rectangle(0.5, h1 + 0.5, w, h - 1);
    cr->stroke();

    int x1 = key_to_x(20.5, w);
    Gdk::Cairo::set_source_rgba(cr, grey1);
    cr->rectangle(1, h1 + 1, x1 - 1, h - 2);
    cr->fill();

    int x2 = key_to_x(109.5, w);
    Gdk::Cairo::set_source_rgba(cr, white);
    cr->rectangle(x1 + 1, h1 + 1, x2 - x1 - 1, h - 2);
    cr->fill();

    Gdk::Cairo::set_source_rgba(cr, grey1);
    cr->rectangle(x2 + 1, h1 + 1, w - x2 - 1, h - 2);
    cr->fill();

    Gdk::Cairo::set_source_rgba(cr, black);

    int clipkey1 = std::max(0, x_to_key_right(clip_low - 1, w));
    int clipkey2 = std::min(x_to_key_right(clip_high - 1, w) + 1, 128);

    for (int i = clipkey1 ; i < clipkey2 ; i++) {
        int note = (i + 3) % 12;
        int x = key_to_x(i, w);

        if (note == 1 || note == 4 || note == 6 ||
            note == 9 || note == 11) {
            // black key: short line in the middle, with a rectangle
            // on top
            int x2 = key_to_x(i + 0.5, w);
            cr->move_to(x2 + 0.5, h1 + bh + 0.5);
            cr->line_to(x2 + 0.5, h1 + h - 1);
            cr->stroke();

            int x3 = key_to_x(i + 1, w);
            cr->rectangle(x, h1 + 1, x3 - x + 1, bh);
            cr->fill();
        } else if (note == 3 || note == 8) {
            // C or F: long line to the left
            cr->move_to(x + 0.5, h1 + 1);
            cr->line_to(x + 0.5, h1 + h - 1);
            cr->stroke();
        }

        if (key_pressed[i]) draw_key(cr, i);

        if (note == 3) draw_digit(cr, i);
    }
}