// Construct the dialog
LightTextureChooser::LightTextureChooser()
:	gtkutil::BlockingTransientWindow(_("Choose texture"), GlobalMainFrame().getTopLevelWindow()),
	_selector(Gtk::manage(new ShaderSelector(this, getPrefixList(), true))) // true >> render a light texture
{
	// Set the default size of the window
	Gdk::Rectangle rect;

	if (GlobalGroupDialog().getDialogWindow()->is_visible())
	{
		rect = gtkutil::MultiMonitor::getMonitorForWindow(GlobalGroupDialog().getDialogWindow());
	}
	else
	{
		rect = gtkutil::MultiMonitor::getMonitorForWindow(GlobalMainFrame().getTopLevelWindow());
	}

	set_default_size(static_cast<int>(rect.get_width()*0.6f), static_cast<int>(rect.get_height()*0.6f));

	// Construct main VBox, and pack in ShaderSelector and buttons panel
	Gtk::VBox* vbx = Gtk::manage(new Gtk::VBox(false, 6));

	vbx->pack_start(*_selector, true, true, 0);
	vbx->pack_start(createButtons(), false, false, 0);

	add(*vbx);
}