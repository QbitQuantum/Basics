void
AppWindow::MessageReceived(BMessage* message)
{
	//PRINT(("AppWindow::MessageReceived(BMessage*)\n"));

	switch(message->what)
	{
		case MSG_FILE_OPEN:
		{
			fOpenPanel->Show();
			break;
		}
		case B_ABOUT_REQUESTED:
			AboutRequested();
			break;

		case MSG_EDITOR_MODE:
			m_app_view->SelectView(0);
			break;
		case MSG_TA_MODE:
			m_app_view->SelectView(1);
			break;
		case MSG_NA_MODE:
			m_app_view->SelectView(2);
			break;
		case MSG_MPEG_MODE:
			m_app_view->SelectView(3);
			break;
#ifdef _TTE_
		case MSG_TT_INFO_MODE:
			m_app_view->SelectView(4);
			break;
#endif
		case MSG_PREVIOUS_MODE:
			m_app_view->SetPreviousMode();
			break;
		case MSG_NEXT_MODE:
			m_app_view->SetNextMode();
			break;

		case MSG_RESET:
			m_app_view->Reset();
			break;
		case MSG_CLEAR_LIST:
			m_app_view->ClearList();
			break;

		case MSG_PREVIOUS_FILE:
			m_app_view->SelectPreviousFile();
			break;
		case MSG_NEXT_FILE:
			m_app_view->SelectNextFile();
			break;

		case MSG_FIRST_FILE:
			m_app_view->SelectFirstFile();
			break;
		case MSG_LAST_FILE:
			m_app_view->SelectLastFile();
			break;

		case B_REFS_RECEIVED:
			m_app_view->MessageReceived(message);
			break;

		case MSG_MAKE_APPLY_BUTTON_DEFAULT:
			m_app_view->m_apply_button->MakeDefault(true);
			break;

		case MSG_MAKE_APPLY_BUTTON_NOT_DEFAULT:
			m_app_view->m_apply_button->MakeDefault(false);
			break;

		case MSG_EDIT_CUT:
			{
				message->what = B_CUT;
				BView *view = CurrentFocus();
				if (view)
					view->MessageReceived(message);
			}
			break;

		case MSG_EDIT_COPY:
			{
				message->what = B_COPY;
				BView *view = CurrentFocus();
				if (view)
					view->MessageReceived(message);
			}
			break;

		case MSG_EDIT_PASTE:
			{
				message->what = B_PASTE;
				BView *view = CurrentFocus();
				if (view)
					view->MessageReceived(message);
			}
			break;

		case MSG_SELECT_ALL:
			{
				message->what = B_SELECT_ALL;
				BView *view = CurrentFocus();
				if (view)
					view->MessageReceived(message);
				else
					m_app_view->SelectAll();
			}
			break;

		case MSG_SELECT_ALL_UNSUPPORTED:
			m_app_view->SelectAllUnsupported();
			break;
		
		case MSG_README:
		{
			BPath path;
			app_info info;
			be_roster->GetActiveAppInfo(&info);
			BEntry entry(&info.ref);
			
			entry.GetPath(&path);
			path.GetParent(&path);
			path.Append(DOCUMENTATION_DIR);
			path.Append(README_FILE);
			
			BMessage message(B_REFS_RECEIVED);
 			message.AddString("url", path.Path());
 			be_roster->Launch("text/html", &message);
			break;
		}

		case MSG_CHANGELOG:
		{
			BPath path;
			app_info info;
			be_roster->GetActiveAppInfo(&info);
			BEntry entry(&info.ref);
			
			entry.GetPath(&path);
			path.GetParent(&path);
			path.Append(DOCUMENTATION_DIR);
			path.Append(CHANGELOG_FILE);
			
			BMessage message(B_REFS_RECEIVED);
 			message.AddString("url", path.Path());
 			be_roster->Launch("text/html", &message);
			break;
		}
		
		default:
			BWindow::MessageReceived(message);
	}
}