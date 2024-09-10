// Create GTK stuff in c-tor
OverlayDialog::OverlayDialog() :
	PersistentTransientWindow(_(DIALOG_TITLE), GlobalMainFrame().getTopLevelWindow(), true),
	_callbackActive(false)
{
	set_border_width(12);

	// Set default size
	Gdk::Rectangle rect = gtkutil::MultiMonitor::getMonitorForWindow(GlobalMainFrame().getTopLevelWindow());
	set_default_size(static_cast<int>(rect.get_width()/3), -1);

	// Pack in widgets
	Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox(false, 12));

	vbox->pack_start(createWidgets(), true, true, 0);
	vbox->pack_end(createButtons(), false, false, 0);

	add(*vbox);
}