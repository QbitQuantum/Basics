	TextureOverviewDialog::~TextureOverviewDialog ()
	{
		// Propagate shortcuts to the main window
		GlobalEventManager().disconnectDialogWindow(GTK_WINDOW(getWindow()));
	}