ParticlesChooser::ParticlesChooser() :
	gtkutil::BlockingTransientWindow(_("Choose particles"), GlobalMainFrame().getTopLevelWindow()),
	_particlesList(Gtk::ListStore::create(COLUMNS())),
	_selectedParticle(""),
	_preview(new gtkutil::ParticlePreview)
{
	set_border_width(12);

	// Set the default size of the window
	const Glib::RefPtr<Gtk::Window>& mainWindow = GlobalMainFrame().getTopLevelWindow();

	Gdk::Rectangle rect = gtkutil::MultiMonitor::getMonitorForWindow(mainWindow);
	int height = static_cast<int>(rect.get_height() * 0.6f);

	set_default_size(
		static_cast<int>(rect.get_width() * 0.4f), height
	);

	// Set the default size of the window
	_preview->setSize(rect.get_width() * 0.2f, height);

	// Main dialog vbox
	Gtk::VBox* vbox = Gtk::manage(new Gtk::VBox(false, 12));

	// Create a horizontal box to pack the treeview on the left and the preview on the right
	Gtk::HBox* hbox = Gtk::manage(new Gtk::HBox(false, 6));

	hbox->pack_start(createTreeView(), true, true, 0);

	Gtk::VBox* previewBox = Gtk::manage(new Gtk::VBox(false, 0));
	previewBox->pack_start(*_preview, true, true, 0);

	hbox->pack_start(*previewBox, true, true, 0);

	vbox->pack_start(*hbox, true, true, 0);
	vbox->pack_end(createButtons(), false, false, 0);

	// Add main vbox to dialog
	add(*vbox);
}