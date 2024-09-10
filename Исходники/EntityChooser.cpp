std::string EntityChooser::ChooseEntity(const std::string& preSelectedEntity)
{
	gtkutil::Dialog dlg(_("Select Entity"), GlobalMainFrame().getTopLevelWindow());

	Gdk::Rectangle rect = gtkutil::MultiMonitor::getMonitorForWindow(GlobalMainFrame().getTopLevelWindow());

	dlg.set_default_size(static_cast<int>(rect.get_width()/2), static_cast<int>(2*rect.get_height()/3));

	// Instantiate a new chooser class
	EntityChooserPtr chooser(new EntityChooser);
	chooser->setSelectedEntity(preSelectedEntity);

	// add this to the dialog window
	IDialog::Handle handle = dlg.addElement(chooser);

	if (dlg.run() == IDialog::RESULT_OK)
	{
		return dlg.getElementValue(handle);
	}
	else
	{
		// Cancelled
		return "";
	}
}