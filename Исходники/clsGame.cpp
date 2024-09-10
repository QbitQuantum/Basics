void clsGame::Setup(void)
{
	bool delayError = false;
	wstring msg1st = L"";
	wstring msg2nd = L"";
	int wc3Instance;
	wchar_t buffer[255] = {NULL};
	wstring title;

	// Count the number of wc3's currently setup
	for (wc3Instance = 0; wc3Instance < 8; wc3Instance++)
	{
		_itow_s(wc3Instance+1, buffer, 10);
		title = L"SC2 #";
		title += buffer;

		clsGame::Handle[wc3Instance] = FindWindow(L"Starcraft II", title.c_str());

		if (clsGame::Handle[wc3Instance] != NULL)
		{
			GetWindowThreadProcessId(clsGame::Handle[wc3Instance], &clsGame::PID[wc3Instance]);
			clsBot::SetupWarcraft(wc3Instance);
		}
		else
		{
			// check if running in sandbox

			clsGame::Handle[wc3Instance] = FindWindow(L"Sandbox:DefaultBox:StarCraft II", title.c_str());

			if (clsGame::Handle[wc3Instance] != NULL)
			{
				GetWindowThreadProcessId(clsGame::Handle[wc3Instance], &clsGame::PID[wc3Instance]);
				clsBot::SetupWarcraft(wc3Instance);
			}
		}
	}

	// Rename the remaining wc3's
	for (wc3Instance = 0; wc3Instance < 8; wc3Instance++)
	{
		if (clsGame::Handle[wc3Instance] == NULL)
		{
			clsGame::Handle[wc3Instance] = FindWindow(L"Starcraft II", L"Starcraft II");

			if (clsGame::Handle[wc3Instance] == NULL)
			{
				// check for sandbox

				clsGame::Handle[wc3Instance] = FindWindow(L"Sandbox:DefaultBox:StarCraft II", L"[#] StarCraft II [#]");

				if (clsGame::Handle[wc3Instance] != NULL)
				{
					GetWindowThreadProcessId(clsGame::Handle[wc3Instance], &clsGame::PID[wc3Instance]);
					clsBot::SetupWarcraft(wc3Instance);

					_itow_s(wc3Instance+1, buffer, 10);
					title = L"SC2 #";
					title += buffer;
					SetWindowText(clsGame::Handle[wc3Instance], title.c_str());
				}
				else
				{
					SendMessage(clsBot::hStatus[wc3Instance], WM_SETTEXT, NULL, (LPARAM)L"Not Found");
				}
			}
			else
			{
				GetWindowThreadProcessId(clsGame::Handle[wc3Instance], &clsGame::PID[wc3Instance]);
				clsBot::SetupWarcraft(wc3Instance);

				_itow_s(wc3Instance+1, buffer, 10);
				title = L"SC2 #";
				title += buffer;
				SetWindowText(clsGame::Handle[wc3Instance], title.c_str());
			}
		}
	
		// Calculate if chat delays are great than leave delays
		SendMessage(clsBot::hLeaveDelay[wc3Instance], WM_GETTEXT, 10, (LPARAM)buffer);
		int delayLeave = _wtoi(buffer);
		SendMessage(clsBot::h1stChatDelay[wc3Instance], WM_GETTEXT, 10, (LPARAM)buffer);
		int delay1stChat = _wtoi(buffer);
		SendMessage(clsBot::h2ndChatDelay[wc3Instance], WM_GETTEXT, 10, (LPARAM)buffer);
		int delay2ndChat = _wtoi(buffer);

		// Check to see if show chat is enabled, then show a warning if it is
		if (SendMessage(clsBot::hShow1stChat, BM_GETCHECK, NULL, NULL) == BST_CHECKED && delay1stChat > delayLeave)
		{
			SendMessage(clsBot::hStatus[wc3Instance], WM_GETTEXT, 255, (LPARAM)&buffer);

			if (wstring(buffer) != L"Not Found")
			{
				msg1st += L"SC2 #";
				_itow_s(wc3Instance+1, buffer, 10);
				msg1st += buffer;
				msg1st += L", ";
				delayError = true;
			}

			if (wc3Instance == 7 && delayError == true)
			{
				msg1st.insert(0, L"1st Chat Delay for ");
				msg1st = msg1st.substr(0, msg1st.find_last_of(L','));
				msg1st += L" is greater than the Leave delay so 1st Chat will never be displayed.";
			}
		}

		if (SendMessage(clsBot::hShow2ndChat, BM_GETCHECK, NULL, NULL) == BST_CHECKED && delay2ndChat > delayLeave)
		{
			SendMessage(clsBot::hStatus[wc3Instance], WM_GETTEXT, 255, (LPARAM)buffer);

			if (wstring(buffer) != L"Not Found")
			{
				msg2nd += L"SC2 #";
				_itow_s(wc3Instance+1, buffer, 10);
				msg2nd += buffer;
				msg2nd += L", ";
				delayError = true;
			}

			if (wc3Instance == 7 && delayError == true && msg2nd != L"")
			{
				msg2nd.insert(0, L"2nd Chat Delay for ");
				msg2nd = msg2nd.substr(0, msg2nd.find_last_of(L','));
				msg2nd += L" is greater than the Leave delay so 2nd Chat will never be displayed.";

				if (msg1st != L"")
					msg2nd.insert(0, L"\n\n");
			}
		}	
	}

	// Display an error if show chats are enabled but the delays are greater than the leave delay
	if (delayError == true)
		MessageBox(NULL, (msg1st + msg2nd).c_str(), L"Warning", MB_ICONWARNING);
}