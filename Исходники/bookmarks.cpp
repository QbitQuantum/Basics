void editbookmark(bookmark * const ptr) {

	if (!bookedit_win) {
		bookedit_win = new Fl_Double_Window(350, 180, _("Edit bookmark"));
		{ bookedit_name = new Fl_Input(60, 20, 265, 25, _("Name:"));
		} // Fl_Input* bookedit_name
		{ bookedit_url = new Fl_Input(60, 55, 265, 25, _("URL:"));
		} // Fl_Input* bookedit_url
		{ Fl_Box* o = new Fl_Box(60, 80, 265, 50, _("The changes get applied immediately."));
			o->align(FL_ALIGN_WRAP);
		} // Fl_Box* o
		{ Fl_Button * o = new Fl_Button(60, 130, 115, 30, _("OK"));
			o->callback(bookedit_ok);
			bookedit_okbtn = o;
		} // Fl_Button* o
		{ Fl_Button* o = new Fl_Button(195, 130, 115, 30, _("Cancel"));
			o->callback(bookedit_cancel);
		} // Fl_Button* o
		bookedit_win->end();
	} // Fl_Double_Window* bookedit_win

	bookedit_name->value(ptr->name);
	bookedit_url->value(ptr->url);
	bookedit_url->activate();

	if (!ptr->url)
		bookedit_url->deactivate();

	bookedit_okbtn->user_data(ptr);

	bookedit_win->show();
}