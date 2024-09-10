static int start_dialog(int argc, char** argv) {
	LaunchWindow* win = new LaunchWindow(370, 195, _("Run Command"));
	win->begin();
		Fl_Box* icon = new Fl_Box(10, 10, 55, 55);
		icon->image(image_run);

		Fl_Box* txt = new Fl_Box(70, 10, 290, 69, _("Enter the name of the application "
													"you would like to run or the URL you would like to view"));
		txt->align(132|FL_ALIGN_INSIDE);

		dialog_input = new Fl_Input(70, 90, 290, 25, _("Open:"));

		Resource rc;
		char     buf[128];

		if(rc.load("ede-launch-history") && rc.get("History", "open", buf, sizeof(buf))) {
			dialog_input->value(buf);

			/* make text appear selected */
			dialog_input->position(0, dialog_input->size());
		}

		in_term = new Fl_Check_Button(70, 125, 290, 25, _("Run in terminal"));
		in_term->down_box(FL_DOWN_BOX);

		Fl_Button* ok = new Fl_Button(175, 160, 90, 25, _("&OK"));
		ok->callback(ok_cb, win);
		Fl_Button* cancel = new Fl_Button(270, 160, 90, 25, _("&Cancel"));
		cancel->callback(cancel_cb, win);
	win->end();
	win->window_icon(run_xpm);
	win->show(argc, argv);

	return Fl::run();
}