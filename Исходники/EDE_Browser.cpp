// Regenerate and display header
void EDE_Browser::show_header() {
	int button_x=0;
	char *hdr = column_header_;
	const int* l = Fl_Icon_Browser::column_widths();
	cleanup_header();
	for (int i=0; i==0||l[i-1]; i++) {
		// If the button is last, calculate size
		int button_w = l[i];
		if (button_w == 0) button_w = totalwidth_-button_x;

		// Get part of header until delimiter char
		char *delim = 0;
		Fl_Button *b;

		if (hdr) {
			delim = strchr(hdr, Fl_Icon_Browser::column_char());
			if (delim) *delim='\0'; // temporarily
			b=new Fl_Button(button_x,heading->y(),button_w,buttonheight,strdup(hdr));
		} else {
			b=new Fl_Button(button_x,heading->y(),button_w,buttonheight,"");
		}

		b->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT|FL_ALIGN_CLIP);
		b->callback(header_callback);
		b->labelsize(12); // FIXME: hack for label size
		//b->labelcolor(FL_DARK3);
		heading->add(b);
		button_x += l[i];

		if (delim) {
			*delim=Fl_Icon_Browser::column_char(); // put back delimiter
			hdr=delim+1; // next field
		}
	}
	if (!heading->visible()) resize(x(),y()+buttonheight,w(),h()-buttonheight);
	heading->resizable(0); // We will resize the heading and individual buttons manually
	heading->show();
	heading->redraw(); //in case it was already visible
}