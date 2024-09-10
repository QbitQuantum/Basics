void
PoorManPreferencesWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_PREF_BTN_DONE:
			PoorManWindow* win;
			PoorManServer* server;
			win = ((PoorManApplication*)be_app)->GetPoorManWindow();
			server = win->GetServer();
	
			PRINT(("Pref Window: sendDir CheckBox: %d\n",
				fSiteView->SendDirValue()));
			server->SetListDir(fSiteView->SendDirValue());
			win->SetDirListFlag(fSiteView->SendDirValue());
			PRINT(("Pref Window: indexFileName TextControl: %s\n",
				fSiteView->IndexFileName()));
			if (server->SetIndexName(fSiteView->IndexFileName()) == B_OK)
				win->SetIndexFileName(fSiteView->IndexFileName());
			PRINT(("Pref Window: webDir: %s\n", fSiteView->WebDir()));
			if (server->SetWebDir(fSiteView->WebDir()) == B_OK) {
				win->SetWebDir(fSiteView->WebDir());
				win->SetDirLabel(fSiteView->WebDir());
			}

			PRINT(("Pref Window: logConsole CheckBox: %d\n", 
				fLoggingView->LogConsoleValue()));
			win->SetLogConsoleFlag(fLoggingView->LogConsoleValue());
			PRINT(("Pref Window: logFile CheckBox: %d\n",
				fLoggingView->LogFileValue()));
			win->SetLogFileFlag(fLoggingView->LogFileValue());
			PRINT(("Pref Window: logFileName: %s\n",
				fLoggingView->LogFileName()));
			win->SetLogPath(fLoggingView->LogFileName());
	
			PRINT(("Pref Window: MaxConnections Slider: %ld\n", 
				fAdvancedView->MaxSimultaneousConnections()));
			server->SetMaxConns(fAdvancedView->MaxSimultaneousConnections());
			win->SetMaxConnections(
				(int16)fAdvancedView->MaxSimultaneousConnections());
	
			if (Lock())
				Quit();
			break;
		case MSG_PREF_BTN_CANCEL:
			if (Lock())
				Quit();
			break;
		case MSG_PREF_SITE_BTN_SELECT:
		{
			// Select the Web Directory, root directory to look in.
			fWebDirFilePanel->SetTarget(this);
			BMessage webDirSelectedMsg(MSG_FILE_PANEL_SELECT_WEB_DIR);
			fWebDirFilePanel->SetMessage(&webDirSelectedMsg);
			if (!fWebDirFilePanel->IsShowing())
				fWebDirFilePanel->Show();
			break;
		}
		case MSG_FILE_PANEL_SELECT_WEB_DIR:
			// handle the open BMessage from the Select Web Directory File Panel
			PRINT(("Select Web Directory:\n"));
			SelectWebDir(message);
			break;
		case MSG_PREF_LOG_BTN_CREATE_FILE:
			// Create the Log File
			fLogFilePanel->Show();
			break;
		case MSG_FILE_PANEL_CREATE_LOG_FILE:
			// handle the save BMessage from the Create Log File Panel
			PRINT(("Create Log File:\n"));
			CreateLogFile(message);
			break;
		case MSG_PREF_ADV_SLD_MAX_CONNECTION:
			fMaxConnections = fAdvancedView->MaxSimultaneousConnections();
			PRINT(("Max Connections: %ld\n", fMaxConnections));
			break;
		default:
			BWindow::MessageReceived(message);
			break;
	}
}