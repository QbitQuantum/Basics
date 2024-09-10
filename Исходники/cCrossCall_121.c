/*	The callback routine for the main window.
	PA: The WM_CREATE  message registers the main window as a clipboard viewer.
		The WM_DESTROY message unregisters the main window.
*/
static LRESULT CALLBACK MainWindowProcedure (HWND hWin, UINT uMess, WPARAM wPara, LPARAM lPara)
{
	switch (uMess)
	{
		case WM_NCPAINT:
			break;
		/*	WM_ENTERIDLE message is used to let Clean evaluate the initialisation action
			of a modal dialog by sending the CcWmIDLEDIALOG message.
		*/
		case WM_ENTERIDLE:
			{
				HWND hwndModalDialog;

				hwndModalDialog = (HWND)lPara;

				if (wPara == MSGF_DIALOGBOX && hwndModalDialog != ghwndLastModalDialog)
				{
					SendMessage1ToClean (CcWmIDLEDIALOG,(int)hwndModalDialog);
					ghwndLastModalDialog = hwndModalDialog;
				}
				else
				{
					SendMessage0ToClean (CcWmIDLETIMER);
				}
				return 0;
			}
			break;
		case WM_TIMER:
			{
				SendMessage2ToClean (CcWmTIMER, wPara, GetMessageTime ());
			}
			break;
		case WM_ENABLE:
			{
				HWND hwin;
				char title[64];

				hwin = GetWindow (ghMainWindow, GW_HWNDFIRST);
				while (hwin != NULL)
				{
					GetWindowText (hwin, title, 63);

					if (GetWindow (hwin, GW_OWNER) == ghMainWindow)
					{
						RECT r;
						GetWindowRect (hwin, &r);
						if (r.top != -1 || r.left != -1 || r.right != 0 || r.bottom != 0)
						{
							EnableWindow (hwin, (BOOL) wPara);
						}
					}
					hwin = GetWindow (hwin, GW_HWNDNEXT);
				}
			}
			break;
		/*	PM_SOCKET_EVENT and PM_DNS_EVENT are intercepted by MainWindowProcedure.
			If ghTCPWindow != NULL, then these messages are passed on to ghTCPWindow.
		*/
		case PM_SOCKET_EVENT:
		case PM_DNS_EVENT:
			{
				if (ghTCPWindow != NULL)
					SendMessage (ghTCPWindow, uMess, wPara, lPara);

				return 0;
			}
			break;
		case WM_DDE_INITIATE:
			{
				static char apptext[256], topictext[256];
				ATOM aApp, aTopic;
/* RWS ... */
				BOOL handleTopic;
/* ... RWS */
				GlobalGetAtomName (HIWORD (lPara), topictext, 256);

				if (lstrcmp (topictext, "CLEANOPEN") == 0)
/* RWS: compare application name */
				{
					GlobalGetAtomName (LOWORD (lPara), apptext, 256);
					handleTopic	= CompareStringA (LOCALE_USER_DEFAULT, NORM_IGNORECASE,
									apptext, lstrlen (apptext), gAppName, lstrlen (gAppName)) == 2;	/* 2 means they are equal */
				}
				else
					handleTopic	= FALSE;

				if (handleTopic)
				{
/* ... RWS */
					aApp = GlobalAddAtom (apptext);
					aTopic = GlobalAddAtom (topictext);
					SendMessage ((HWND) wPara, WM_DDE_ACK, (WPARAM) hWin, MAKELONG (aApp, aTopic));
					GlobalDeleteAtom (aApp);
					GlobalDeleteAtom (aTopic);
				}
				else
				{
					return DefWindowProc (hWin, uMess, wPara, lPara);
				}
			}
			break;
		case WM_DDE_EXECUTE:
			{
				char *commandstring;
				char *pcommand;
				int len;
				union
				{
					DDEACK ddeack;
					WORD w;
				}	da;

				pcommand = GlobalLock ((HANDLE) lPara);
				len = lstrlen (pcommand) + 1;
				commandstring = rmalloc (len);	/* this pointer is passed to and freed in the Clean code. */
				lstrcpyn (commandstring, pcommand, len);
				GlobalUnlock ((HANDLE) lPara);

				SendMessage1ToClean (CcWmDDEEXECUTE, commandstring);

				da.ddeack.bAppReturnCode = 0;
				da.ddeack.fBusy = 0;
				da.ddeack.fAck = 1;
				PostMessage ((HWND) wPara, WM_DDE_ACK, (WPARAM) hWin, PackDDElParam (WM_DDE_ACK, (UINT) da.w, lPara));
				return 0;
			}
			break;
		case WM_DDE_TERMINATE:
			{
				PostMessage ((HWND) wPara, WM_DDE_TERMINATE, (WPARAM) hWin, 0);
			} return 0;
		default:
			return DefWindowProc (hWin, uMess, wPara, lPara);
			break;
	}
	return 0;
}	/*	MainWindowProcedure */