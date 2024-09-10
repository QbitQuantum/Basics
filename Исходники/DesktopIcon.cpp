static void rename_cb(Fl_Widget*, void* d) {
	DesktopIcon* di = (DesktopIcon*)d;

	const char* new_name = input(_("New name"), di->label());
	di->rename(new_name);
}