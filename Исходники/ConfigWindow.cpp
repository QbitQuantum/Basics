void
ConfigWindow::_RevertToLastSettings()
{
	// revert general settings
	BMailSettings settings;

	status_t status = _SetToGeneralSettings(&settings);
	if (status != B_OK) {
		char text[256];
		sprintf(text, B_TRANSLATE(
				"\nThe general settings couldn't be reverted.\n\n"
				"Error retrieving general settings:\n%s\n"),
			strerror(status));
		BAlert* alert = new BAlert(B_TRANSLATE("Error"), text,
			B_TRANSLATE("OK"), NULL, NULL, B_WIDTH_AS_USUAL, B_WARNING_ALERT);
		alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
		alert->Go();
	}

	// revert account data

	if (fAccountsListView->CurrentSelection() != -1)
		_ReplaceConfigView(_BuildHowToView());

	for (int32 i = 0; i < fAccounts.CountItems(); i++) {
		BMailAccountSettings* account = fAccounts.ItemAt(i);
		_RemoveAccountFromListView(account);
		delete account;
	}

	fAccounts.MakeEmpty();
	_LoadAccounts();
}