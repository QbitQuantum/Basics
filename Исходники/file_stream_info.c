INT_PTR CALLBACK 
fssi_WindowHandler(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    const static DWORD dwStreamSize = 1024 * sizeof(FILE_STREAM_INFO);
    __declspec (align(64)) static PFILE_STREAM_INFO pfsi;
    static HANDLE hFile = nullptr;
    static HWND   hListView = nullptr;
    static HWND   hCreateButton = nullptr;
    switch ( uMsg ) {
  	    case WM_INITDIALOG: {
            hCreateButton = GetDlgItem(hDlg, IDC_CREATE_STREAM);
			hListView = GetDlgItem(hDlg, IDC_STREAM_LIST);
			pfsi = (PFILE_STREAM_INFO)LocalAlloc(LPTR, dwStreamSize);			
			private_InitListView(hListView);
		    return TRUE;
        }
		case WM_COMMAND: {
			switch ( LOWORD(wParam) ) {
		    case IDM_VIEW_STREAM: {
					LPTSTR lpstrFileName;
					INT iSelected;
					

					iSelected = ListView_GetSelectionMark(hListView);
					if ( iSelected >= 0 ) {
						TCHAR szName[(MAX_PATH + 64) * sizeof(TCHAR)];
						ListView_GetItemText(hListView, iSelected, 1, szName, sizeof(szName));
						lpstrFileName = private_GetStreamName(hFile, szName);
						if ( lpstrFileName ) {
                            MessageBox(hDlg, lpstrFileName, nullptr, 0);
							LocalFree(lpstrFileName);
						}
					}
					break;
				}
                case IDC_CREATE_STREAM:
				case IDM_CREATE_STREAM: {
					LPTSTR lpstrFileName;

					lpstrFileName = private_GetStreamName(hFile, TEXT(""));
					if ( lpstrFileName ) {
						LocalFree(lpstrFileName);
					}
					break;
				}
			}
			break;
		}
		case WM_NOTIFY: {
			LPNMHDR hdr = (LPNMHDR)lParam;
			switch (hdr->code) { 
		        case NM_RCLICK: {
					/** Or WM_MENUCOMMAND */
					if ( hdr->idFrom == IDC_STREAM_LIST ) {
						HMENU hStreamMenu;
			            BOOL bView = FALSE;
                        UINT uFlags;
						POINT p;

						GetCursorPos(&p);
			            uFlags = MF_BYPOSITION | MF_STRING | MF_POPUP;
			            bView = ListView_GetSelectedCount(hListView) != 0;
			            if ( !bView )
                            uFlags |= MF_DISABLED;
						if ( ListView_GetItemCount(hListView) == 0 )
							break;
						hStreamMenu = CreatePopupMenu();
			            AppendMenu(hStreamMenu, uFlags, IDM_VIEW_STREAM,   TEXT("Посмотреть"));
                        AppendMenu(hStreamMenu, MF_BYPOSITION | MF_STRING, IDM_CREATE_STREAM, TEXT("Создать"));
                        SetForegroundWindow(hListView);
                        TrackPopupMenu(hStreamMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hListView, nullptr);
			            DestroyMenu(hStreamMenu);
					}
					break;
			    }
			}
			break;
		}
	  case WM_SETFILE_HANDLE: {
		  BOOL bClear;
		  hFile = (HANDLE)lParam;
		  if ( hFile && hFile != INVALID_HANDLE_VALUE ) {
			  BOOL bResult;
			  bClear = FALSE;
			  bResult = GetFileInformationByHandleEx(hFile, FileStreamInfo, pfsi, dwStreamSize);
			  if ( bResult ) {
					LVITEM	lvItem;
					TCHAR   szSubBuffer[1024];
					INT nIndex;
                    DWORD dwOffset;
					PFILE_STREAM_INFO pInfo;

					dwOffset = 0;
					nIndex = 0;
                    pInfo = pfsi;
					ListView_DeleteAllItems(hListView);
					ZeroMemory( &lvItem, sizeof(lvItem) );
	                lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE; 
	                lvItem.state = 0; 
	                lvItem.stateMask = 0;
					while (TRUE) {
						lvItem.iItem = nIndex;
		                lvItem.iSubItem = 0;
						StringCchPrintf( szSubBuffer, sizeof(szSubBuffer), TEXT("%d"), nIndex);
		                lvItem.pszText = szSubBuffer;
		                lvItem.cchTextMax = lstrlen( szSubBuffer );
		                ListView_InsertItem( hListView, &lvItem );
                        /** Name */
						//StringCchPrintf( szSubBuffer, sizeof(szSubBuffer), TEXT("%*.*S"), pInfo->StreamNameLength / 2, pInfo->StreamNameLength / 2, pInfo->StreamName );
						StringCchPrintf( szSubBuffer, sizeof(szSubBuffer), TEXT("%s"), pInfo->StreamName );
						ListView_SetItemText( hListView, nIndex, 1, szSubBuffer );
						/** Size */
						StringCchPrintf( szSubBuffer, sizeof(szSubBuffer), TEXT("%I64u"), pInfo->StreamSize);
						ListView_SetItemText( hListView, nIndex, 2, szSubBuffer );
						/** Allocated size */
						StringCchPrintf( szSubBuffer, sizeof(szSubBuffer), TEXT("%I64u"), pInfo->StreamAllocationSize);
						ListView_SetItemText( hListView, nIndex, 3, szSubBuffer );
						++nIndex;
						if ( !pInfo->NextEntryOffset )
							break;
						pInfo = (PFILE_STREAM_INFO)( (LPBYTE)pInfo + pInfo->NextEntryOffset );
					}
			  } else {
				  bClear = TRUE;
			  }
		  } else {
			  bClear = TRUE;
		  }

		  if ( bClear ) {
			  ListView_DeleteAllItems(hListView);
		  }

          EnableWindow(hCreateButton, hFile != nullptr);
		  break;
	  }
	  case WM_RESETFILE_HANDLE: {
          hFile = nullptr;
		  break;
	  }
	  case WM_CLOSE:
	  case WM_DESTROY: {
		  LocalFree(pfsi);
		  break;
	  }
  }
  return FALSE;
}