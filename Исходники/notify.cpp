int main() {
	fl_open_display();

	Fl_Double_Window* win = new Fl_Double_Window(295, 144, "Notify test");
	win->begin();
		txt = new Fl_Input(10, 15, 275, 25);
		txt->align(FL_ALIGN_TOP_LEFT);

		color_button = new Fl_Button(260, 50, 25, 25, "Color");
		color_button->align(FL_ALIGN_LEFT);
		color_button->callback(color_cb);
		Fl_Box* bx = new Fl_Box(10, 50, 164, 85, "Type some text and choose color, then press Send. "
		"Desktop should get notified about this.");
		bx->align(FL_ALIGN_WRAP);

		Fl_Button* send_button = new Fl_Button(195, 110, 90, 25, "&Send");
		send_button->callback(send_cb);
	win->end();
	win->show();
	return Fl::run();
}