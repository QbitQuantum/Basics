    window(int x, int y, int w, int h, const char *label = 0)
        : Fl_Window(x, y, w, h, label)
    {
        Fl_Box *o = new Fl_Box(10, 10, 300, 25,
            "Open CSV file to convert to HTML -->");
        o->box(FL_BORDER_BOX);
        o->align(FL_ALIGN_INSIDE | FL_ALIGN_WRAP| FL_ALIGN_CENTER);
        o->color((Fl_Color)215);
        o->labelfont(FL_HELVETICA_BOLD);

        Fl_Button *but = new Fl_Button(320, 10, 80, 25, "Pick Files");
        but->callback(on_pick_button_click, this);

        encode_check = new Fl_Check_Button(10, 40, 280, 25,
            "Escape special HTML characters.");
        encode_check->value(1);

        open_file_check = new Fl_Check_Button(10, 65, 280, 25,
            "Open HTML in browser.");
        open_file_check->value(1);

        Fl_Button *author = new Fl_Button(320, 65, 80, 25, "Mingjie Li");
        author->box(FL_FLAT_BOX);
        author->align(FL_ALIGN_INSIDE | FL_ALIGN_RIGHT);
        author->labelsize(12);
        author->labelcolor(fl_rgb_color(128, 128, 128));
        author->callback(on_author_click, this);
    }