void DeskbarPulseView::MessageReceived(BMessage *message) {
	switch (message->what) {
		case PV_NORMAL_MODE:
			SetMode(true);
			Remove();
			break;
		case PV_MINI_MODE:
			SetMode(false);
			Remove();
			break;
		case PV_PREFERENCES:
			if (prefswindow != NULL) {
				prefswindow->Activate(true);
				break;
			}
			prefswindow = new PrefsWindow(prefs->prefs_window_rect,
				"Pulse settings", new BMessenger(this), prefs);
			prefswindow->Show();
			break;
		case PV_ABOUT: {
			PulseApp::ShowAbout(false);
			break;
		}
		case PV_QUIT:
			Remove();
			break;
		case PRV_DESKBAR_CHANGE_COLOR:
			UpdateColors(message);
			break;
		case PRV_DESKBAR_ICON_WIDTH: {
			int width = message->FindInt32("width");
			ResizeTo(width - 1, 15);
			Draw(Bounds());
			break;
		}
		case PV_REPLICANT_PULSE:
			Update();
			Draw(Bounds());
			break;
		case PRV_QUIT:
			prefswindow = NULL;
			break;
		case PV_CPU_MENU_ITEM:
			ChangeCPUState(message);
			break;
		default:
			BView::MessageReceived(message);
			break;
	}
}