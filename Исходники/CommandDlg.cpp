void CommandDlg::handleOKClicked() {
	name = nameBox->getText();
	if((type != 0) && (name.empty() || commandBox->getText().empty())) {
		createMessageBox().show(T_("Name and command must not be empty"), _T(APPNAME) _T(" ") _T(VERSIONSTRING), MessageBox::BOX_OK, MessageBox::BOX_ICONEXCLAMATION);
		return;
	}

	ctx = 0;
	if(hubMenu->getChecked())
		ctx |= UserCommand::CONTEXT_HUB;
	if(userMenu->getChecked())
		ctx |= UserCommand::CONTEXT_CHAT;
	if(searchMenu->getChecked())
		ctx |= UserCommand::CONTEXT_SEARCH;
	if(fileListMenu->getChecked())
		ctx |= UserCommand::CONTEXT_FILELIST;

	hub = hubBox->getText();

	if(type != 0)
		type = once->getChecked() ? 2 : 1;

	SettingsManager::getInstance()->set(SettingsManager::OPEN_USER_CMD_HELP, openHelp->getChecked());

	endDialog(IDOK);
}