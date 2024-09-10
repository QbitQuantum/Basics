// Constructor
SoundChooser::SoundChooser() :
	BlockingTransientWindow(_("Choose sound"), GlobalMainFrame().getTopLevelWindow()),
	_treeStore(Gtk::TreeStore::create(_columns)),
	_treeView(NULL),
	_preview(Gtk::manage(new SoundShaderPreview))
{
	set_border_width(12);
	set_type_hint(Gdk::WINDOW_TYPE_HINT_DIALOG);

	// Set the default size of the window
	Gdk::Rectangle rect = gtkutil::MultiMonitor::getMonitorForWindow(GlobalMainFrame().getTopLevelWindow());
	set_default_size(rect.get_width() / 2, rect.get_height() / 2);

	// Main vbox
	Gtk::VBox* vbx = Gtk::manage(new Gtk::VBox(false, 12));

    vbx->pack_start(createTreeView(), true, true, 0);
    vbx->pack_start(*_preview, false, false, 0);
    vbx->pack_start(createButtons(), false, false, 0);

    add(*vbx);
}