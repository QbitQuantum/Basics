int main(int argc, char** argv)
{
	// Check config option, if showing is disabled, exit
	Fl_Config conf("EDE Team", "etip");
	if(argc == 2 && (!strcmp(argv[1], "-f") || !strcmp(argv[1], "--force")))
	{
		// nothing, to simplify omiting those '!'
	}
	else
	{
		bool show = true;
		conf.set_section("Tips");
		conf.read("Show", show, true);
		if (!show)
			return 0;
	}
	
	conf_global = &conf;
	srand(time(NULL));
	fl_init_locale_support("etip", PREFIX"/share/locale");

	Fl_Window* win = new Fl_Window(420, 169, _("Tips..."));
	win->shortcut(0xff1b);
	win->begin();

	Fl_Group* gr = new Fl_Group(5, 5, 410, 130);
	gr->box(FL_DOWN_BOX);
	Fl_Box* img = new Fl_Box(5, 5, 70, 65);
	Fl_Image pix(hint_xpm);
	img->image(pix);

	Fl_Box* title = new Fl_Box(80, 10, 320, 25, random_txt(title_tips, TITLE_TIPS_NUM));
	title->label_font(fl_fonts+1);
	title->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	title->box(FL_FLAT_BOX);

	Fl_Box* tiptxt = new Fl_Box(80, 45, 320, 75, random_txt(tiplist, TIPS_NUM));
	tiptxt->align(FL_ALIGN_LEFT|FL_ALIGN_TOP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
	tiptxt->box(FL_FLAT_BOX);
	gr->end();

	Fl_Check_Button* ch = new Fl_Check_Button(5, 140, 150, 25, _(" Do not bother me"));
	show_check = ch;

	Fl_Button* prev = new Fl_Button(160, 140, 80, 25, "<-");
	prev->label_font(fl_fonts+1);
	prev->callback(prev_cb, tiptxt);

	Fl_Button* next = new Fl_Button(245, 140, 80, 25, "->");
	next->label_font(fl_fonts+1);
	next->callback(next_cb, tiptxt);
	
	Fl_Button* close = new Fl_Button(335, 140, 80, 25, _("&Close"));
	close->callback(close_cb, win);

	win->end();

	win->set_modal();
	win->show();
	return Fl::run();
}