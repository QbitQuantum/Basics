ULONG 
FANCONTROL::DlgProc(HWND hwnd, ULONG msg, WPARAM mp1, LPARAM mp2)
{
	ULONG rc= 0;
		switch (msg) 
			{
			case WM_INITDIALOG:
				break;
			case WM_TIMER:
				switch (mp1)
				{
				case 1:	
					::PostMessage(this->hwndDialog, WM__GETDATA, 0, 0);
					if (tried2connect)
					{
						if (this->ShowTempIcon==1) 
						{
							this->ProcessTextIcons();  //icon Einstieg
						}
						else 
						{
							this->RemoveTextIcons();
						}

						if (this->pTaskbarIcon)
						{
							this->pTaskbarIcon->SetIcon(this->iFarbeIconB);

							if (_isConnected == FALSE)this->pTaskbarIcon->SetTooltip("not connected to tpfc service");
							else this->pTaskbarIcon->SetTooltip(Title2);

							if (_isConnected == TRUE && _hasShownConnected == FALSE){
									this->pTaskbarIcon->SetBalloon(NIIF_INFO, "TPFanControl Icon",
									"connected to TPFanControl service",11);
									_hasShownConnected = TRUE;}
							if (_isConnected == FALSE && _hasShownDisconnected == FALSE){
									this->pTaskbarIcon->SetBalloon(NIIF_ERROR, "TPFanControl Icon",
									"NOT connected to TPFanControl service",11);
									_hasShownDisconnected = TRUE;}
						}
					}
					break;
				default:
					break;

				}	//switch(mp1)



			//say windows not to hold much more memspace
            SetProcessWorkingSetSize(GetCurrentProcess(),65536,WANTED_MEM_SIZE);
			break;

		case WM_COMMAND:
				if (HIWORD(mp1)==BN_CLICKED || HIWORD(mp1)==EN_CHANGE) 
				{
					int cmd= LOWORD(mp1);

					switch (cmd) {
						case 5001: // bios
						case 5002: // smart
								   break;

						case 5010: // show window
								   ::ShowWindow(this->hwndDialog, TRUE);
								   ::SetForegroundWindow(this->hwndDialog);
								   break;

						case 5050: // donate
								   ::ShellExecute(NULL, "open", Title4, //"http://www.staff.uni-marburg.de/~schmitzr/donate.html", 
									   NULL, NULL, SW_SHOW);
								   break;

						case 5070: // show old temp icon
								   this->ShowTempIcon = NULL;
								   this->pTaskbarIcon= new	TASKBARICON(this->hwndDialog, 11, Title2);
								   //this->pTaskbarIcon->SetIcon(this->iFarbeIconB);
								   break;

						case 5080: // show temp icon
									delete this->pTaskbarIcon;
									this->pTaskbarIcon= NULL;
									this->ShowTempIcon = 1;
									break;

						case 5030: // hide window
								::CloseWindow(this->hwndDialog);
								break;

						case 5020: // end program
							::KillTimer(this->hwndDialog, m_titleTimer);
							::PostMessage(hwnd, WM__DISMISSDLG, IDCANCEL, 0); // exit from ProcessDialog() 
							break;
					}
				}
				break;

		case WM_CLOSE:
			::CloseWindow(this->hwndDialog);
				break;
		case WM_MOVE:
				break;
		case WM_SIZE:
				if (mp1==SIZE_MINIMIZED) {
				    ::ShowWindow(this->hwndDialog, FALSE);
				}
				rc= TRUE;
				break;
		case WM_DESTROY:
				break;

		//
		// USER messages
		//

		case WM__GETDATA:
			if (!this->hThread)
			{
				this->hThread= this->CreateThread(FANCONTROL_Thread, (ULONG)this);
			}
			break;


		case WM__NEWDATA:
	/*			if (this->hThread) {
					::WaitForSingleObject(this->hThread, INFINITE);
					::CloseHandle(this->hThread);
					this->hThread= 0;
				}
	*/
			break;

		case WM__TASKBAR:

				switch (mp2) 
				{
				    case WM_LBUTTONDOWN:
						if (!IsWindowVisible(this->hwndDialog))
						{
								::ShowWindow(this->hwndDialog, TRUE);
								::SetForegroundWindow(this->hwndDialog);
						}
						else	::CloseWindow(this->hwndDialog);
				        break;
				    case WM_LBUTTONUP:
						{
						BOOL 
						isshift= ::GetAsyncKeyState(VK_SHIFT) & 0x8000,
						isctrl= ::GetAsyncKeyState(VK_CONTROL) & 0x8000;
									int action= -1;
								// some fancy key dependent stuff could be done here
						}
						break;
				    case WM_LBUTTONDBLCLK:
						if (!IsWindowVisible(this->hwndDialog)){
								::ShowWindow(this->hwndDialog, TRUE);
								::SetForegroundWindow(this->hwndDialog);
						}
						else	::CloseWindow(this->hwndDialog);
				        break;
				    case WM_RBUTTONDOWN:
								{
								MENU m(5000);
									if (!IsWindowVisible(this->hwndDialog))
										m.DeleteMenuItem(5030);
									if (IsWindowVisible(this->hwndDialog))
										m.DeleteMenuItem(5010);
									if (this->ShowTempIcon == 0)
										m.DeleteMenuItem(5070);
									if (this->ShowTempIcon == 1)
										m.DeleteMenuItem(5080);
								m.Popup(this->hwndDialog);  
						}
						break;
				}
				rc= TRUE;
				break;
		default:
		break;
	}
	return rc;
}