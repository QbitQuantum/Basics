static void SendWordToServer()
{
DWORD_PTR SendMsgAnswer;
DWORD flags;
LRESULT lr;

	if( !IsWindow( GlobalData->ServerWND ) )
		return;

	// Ask for needing to retrieve word - WPARAM = 1
	lr = SendMessageTimeout(GlobalData->ServerWND, WM_MY_SHOW_TRANSLATION, 1, 0, SMTO_ABORTIFHUNG, MOUSEOVER_INTERVAL, &SendMsgAnswer);
	if( lr == 0 || SendMsgAnswer == 0)	//No answer or no needing
		return;

	flags = SendMsgAnswer;

	if (hGetWordLib == 0 && ( flags & GD_FLAG_METHOD_STANDARD ) ) {
		hGetWordLib = LoadLibraryW(GlobalData->LibName);
		if (hGetWordLib) {
			GetWordProc = (GetWordProc_t)GetProcAddress(hGetWordLib, "__gdGetWord");
		}
		else {
			hGetWordLib = INVALID_HANDLE_VALUE;
		}
	}

	GlobalData->CurMod.MatchedWord[0] = 0;
	GlobalData->CurMod.WordLen = 0;
	GlobalData->CurMod.BeginPos = 0;

	if( ( flags & GD_FLAG_METHOD_GD_MESSAGE ) != 0 && uGdAskMessage != 0 ) {
		int n;
		gds.dwSize = sizeof(gds);
		gds.cwData = Buffer;
		gds.dwMaxLength = sizeof(Buffer) / sizeof(Buffer[0]);
		Buffer[0] = 0;
		gds.hWnd = GlobalData->LastWND;
		gds.Pt = GlobalData->LastPt;
		lr = SendMessageTimeout(gds.hWnd, uGdAskMessage, 0, (LPARAM)&gds, SMTO_ABORTIFHUNG, REQUEST_MESSAGE_INTERVAL, &SendMsgAnswer);
		if(lr != 0 && SendMsgAnswer != 0) {
			n = WideCharToMultiByte(CP_UTF8, 0, gds.cwData, lstrlenW(gds.cwData), GlobalData->CurMod.MatchedWord, sizeof(GlobalData->CurMod.MatchedWord) - 1, 0, 0);
			GlobalData->CurMod.MatchedWord[n] = 0;
			GlobalData->CurMod.WordLen = n;
			GlobalData->CurMod.BeginPos = 0;
			if(n > 0) {
				if( IsWindow( GlobalData->ServerWND ) ) {
#ifdef __WIN64
					GlobalData32->LastWND = HandleToLong( GlobalData->LastWND );
					GlobalData32->CurMod.WordLen = n;
					GlobalData32->CurMod.BeginPos = 0;
					lstrcpyn( GlobalData32->CurMod.MatchedWord, GlobalData->CurMod.MatchedWord, sizeof( GlobalData32->CurMod.MatchedWord ) );
#endif
					SendMessageTimeout(GlobalData->ServerWND, WM_MY_SHOW_TRANSLATION, 0, 0, SMTO_ABORTIFHUNG, MOUSEOVER_INTERVAL, &SendMsgAnswer);
				}
			}
			return;
		}
	}

	if( ( flags & GD_FLAG_METHOD_STANDARD ) != 0 && GetWordProc != 0 ) {
		GlobalData->CurMod.WND = GlobalData->LastWND;
		GlobalData->CurMod.Pt = GlobalData->LastPt;

		GetWordProc(&(GlobalData->CurMod));

		if (GlobalData->CurMod.WordLen > 0) {
			if( IsWindow( GlobalData->ServerWND ) ) {
#ifdef __WIN64
				GlobalData32->LastWND = HandleToLong( GlobalData->LastWND );
				GlobalData32->CurMod.WordLen = GlobalData->CurMod.WordLen;
				GlobalData32->CurMod.BeginPos = GlobalData->CurMod.BeginPos;
				lstrcpyn( GlobalData32->CurMod.MatchedWord, GlobalData->CurMod.MatchedWord, sizeof( GlobalData32->CurMod.MatchedWord ) );
#endif
				SendMessageTimeout(GlobalData->ServerWND, WM_MY_SHOW_TRANSLATION, 0, 0, SMTO_ABORTIFHUNG, MOUSEOVER_INTERVAL, &SendMsgAnswer);
			}
			return;
		}
	}

	if( ( flags & GD_FLAG_METHOD_IACCESSIBLEEX ) != 0 ) {
		getWordByAccEx( GlobalData->LastPt );
		if (GlobalData->CurMod.WordLen > 0 ) {
			if( IsWindow( GlobalData->ServerWND ) ) {
#ifdef __WIN64
				GlobalData32->LastWND = HandleToLong( GlobalData->LastWND );
				GlobalData32->CurMod.WordLen = GlobalData->CurMod.WordLen;
				GlobalData32->CurMod.BeginPos = GlobalData->CurMod.BeginPos;
				lstrcpyn( GlobalData32->CurMod.MatchedWord, GlobalData->CurMod.MatchedWord, sizeof( GlobalData32->CurMod.MatchedWord ) );
#endif
				SendMessageTimeout(GlobalData->ServerWND, WM_MY_SHOW_TRANSLATION, 0, 0, SMTO_ABORTIFHUNG, MOUSEOVER_INTERVAL, &SendMsgAnswer);
			}
			return;
		}
	}

	if( ( flags & GD_FLAG_METHOD_UI_AUTOMATION ) != 0 && IsWindow( GlobalData->ServerWND ) ) {
		PostMessage( GlobalData->ServerWND, WM_MY_SHOW_TRANSLATION, 0, 0 );
	}		
}