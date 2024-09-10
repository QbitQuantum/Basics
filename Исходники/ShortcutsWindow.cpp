bool
ShortcutsWindow::QuitRequested()
{
	bool ret = true;

	if (fKeySetModified) {
		BAlert* alert = new BAlert(WARNING, 
			B_TRANSLATE("Save changes before closing?"),
			B_TRANSLATE("Cancel"), B_TRANSLATE("Don't save"),
			B_TRANSLATE("Save"));
		alert->SetShortcut(0, B_ESCAPE);
		alert->SetShortcut(1, 'd');
		alert->SetShortcut(2, 's');
		switch(alert->Go()) {
			case 0:
				ret = false;
				break;

			case 1:
				ret = true;
				break;

			case 2:
				// Save: automatically if possible, otherwise go back and open
				// up the file requester
				if (fLastSaved.InitCheck() == B_OK) {
					if (_SaveKeySet(fLastSaved) == false) {
						BAlert* alert = new BAlert(ERROR, 
							B_TRANSLATE("Shortcuts was unable to save your "
								"KeySet file!"), 
							B_TRANSLATE("Oh no"));
						alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
						alert->Go();
						ret = true; //quit anyway
					}
				} else {
					PostMessage(SAVE_KEYSET);
					ret = false;
				}
				break;
		}
	}

	if (ret) {
		fColumnListView->DeselectAll();

		// Save the window position.
		entry_ref ref;
		if (_GetWindowSettingsFile(&ref)) {
			BEntry entry(&ref);
			_SaveWindowSettings(entry);
		}
	}
	
	return ret;
}