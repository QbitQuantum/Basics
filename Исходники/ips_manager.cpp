static INT_PTR CALLBACK DefInpProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
		case WM_INITDIALOG: {
			hIpsDlg = hDlg;
			
			hWhiteBGBrush = CreateSolidBrush(RGB(0xFF,0xFF,0xFF));
			hPreview = PNGLoadBitmap(hIpsDlg, NULL, 304, 228, 2);
			SendDlgItemMessage(hIpsDlg, IDC_SCREENSHOT_H, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hPreview);
			
			LONG_PTR Style;
			Style = GetWindowLongPtr (GetDlgItem(hIpsDlg, IDC_TREE1), GWL_STYLE);
			Style |= TVS_CHECKBOXES;
			SetWindowLongPtr (GetDlgItem(hIpsDlg, IDC_TREE1), GWL_STYLE, Style);
		
			IpsManagerInit();

			WndInMid(hDlg, hScrnWnd);
			SetFocus(hDlg);											// Enable Esc=close
			break;
		}
		
		case WM_COMMAND: {
			int wID = LOWORD(wParam);
			int Notify = HIWORD(wParam);
						
			if (Notify == BN_CLICKED) {
				switch (wID) {
					case IDOK: {
						IpsOkay();
						break;
					}
				
					case IDCANCEL: {
						SendMessage(hDlg, WM_CLOSE, 0, 0);
						return 0;
					}
					
					case IDC_IPSMAN_DESELECTALL: {
						for (int i = 0; i < nNumPatches; i++) {
							for (int j = 0; j < nNumPatches; j++) {
								_TreeView_SetCheckState(hIpsList, hPatchHandlesIndex[j], FALSE);
							}
						}
						break;
					}
				}
			}
			
			if (wID == IDC_CHOOSE_LIST && Notify == CBN_SELCHANGE) {
				nIpsSelectedLanguage = SendMessage(GetDlgItem(hIpsDlg, IDC_CHOOSE_LIST), CB_GETCURSEL, 0, 0);
				TreeView_DeleteAllItems(hIpsList);
				FillListBox();
				RefreshPatch();
				return 0;
			}
			
			break;
		}
		
		case WM_NOTIFY: {
			NMHDR* pNmHdr = (NMHDR*)lParam;
			
			if (LOWORD(wParam) == IDC_TREE1 && pNmHdr->code == TVN_SELCHANGED) {
				RefreshPatch();
				
				return 1;
			}
			
			if (LOWORD(wParam) == IDC_TREE1 && pNmHdr->code == NM_DBLCLK) {
				// disable double-click node-expand
				SetWindowLongPtr(hIpsDlg, DWLP_MSGRESULT, 1);

				return 1;
			}
			
			if (LOWORD(wParam) == IDC_TREE1 && pNmHdr->code == NM_CLICK) {
				POINT cursorPos;
				GetCursorPos(&cursorPos);
				ScreenToClient(hIpsList, &cursorPos);

				TVHITTESTINFO thi;
				thi.pt = cursorPos;
				TreeView_HitTest(hIpsList, &thi);

				if (thi.flags == TVHT_ONITEMSTATEICON) {
					TreeView_SelectItem(hIpsList, thi.hItem);
				}
			
				return 1;
			}

			SetWindowLongPtr(hIpsDlg, DWLP_MSGRESULT, CDRF_DODEFAULT);
			return 1;
		}
	
		case WM_CTLCOLORSTATIC: {
			if ((HWND)lParam == GetDlgItem(hIpsDlg, IDC_TEXTCOMMENT)) {
				return (BOOL)hWhiteBGBrush;
			}
			break;
		}
		
		case WM_CLOSE: {
			IpsManagerExit();
			break;
		}
	}

	return 0;
}