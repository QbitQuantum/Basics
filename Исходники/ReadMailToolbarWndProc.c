LRESULT WINAPI 
ReadMailToolbarWndProc(HWND hwnd, 
					   UINT msg, 
					   WPARAM wParam, 
					   LPARAM lParam)
{
	WNDPROC lpOldProc;

	lpOldProc = (WNDPROC)GetProp( hwnd, "oldproc" );
   
	switch(msg)
	{
		case WM_DESTROY:   
		{
			//  Put back old window proc and
			SetWindowLong( hwnd, GWL_WNDPROC, (DWORD)lpOldProc );

			//  remove window property
			RemoveProp( hwnd, "oldproc" ); 
			break;
		}

		case WM_NOTIFY:
		{
			static char szTooltip[256] = {0x00};
			LPTOOLTIPTEXT lpToolTipText = (LPTOOLTIPTEXT) lParam;;

			switch (((LPNMHDR)lParam)->code)
			{
				case TTN_NEEDTEXTA:
				{
					if(lpToolTipText->hdr.idFrom >= IDC_DECRYPT && 
						lpToolTipText->hdr.idFrom <= IDC_MIME )
					{
						int StringId = lpToolTipText->hdr.idFrom -  
										WM_USER - 1000;

						LoadString (g_hinst, 
									StringId,
									szTooltip,
									sizeof(szTooltip));

						lpToolTipText->lpszText = szTooltip;

						if(g_hwndEudoraStatusbar)
						{
							SendMessage(g_hwndEudoraStatusbar,
										SB_SETTEXT,
										(WPARAM)0,
										(LPARAM)szTooltip);
						}
						
						return 0;
					}
				}

				case TTN_NEEDTEXTW:
				{
					static wchar_t wideBuf[256];

					if(lpToolTipText->hdr.idFrom >= IDC_DECRYPT && 
						lpToolTipText->hdr.idFrom <= IDC_MIME )
					{
						int StringId = lpToolTipText->hdr.idFrom - 
										WM_USER - 1000;
					
    					LoadString (g_hinst, 
									StringId,
									szTooltip,
									sizeof(szTooltip));

						MultiByteToWideChar(CP_ACP, 
											MB_PRECOMPOSED, 
											szTooltip, 
											-1, 
											wideBuf, 
											256);

						lpToolTipText->lpszText = (char*)wideBuf;

						if(g_hwndEudoraStatusbar)
						{
							SendMessage(g_hwndEudoraStatusbar,
										SB_SETTEXT,
										(WPARAM)0,
										(LPARAM)szTooltip);
						}

						return 0;
					}
				}
			}
			break;
		}

		case WM_COMMAND:
		{
			HWND hwndParent = NULL;
			HWND hwndRichEdit = NULL;

			switch(wParam)
			{
				case IDC_DECRYPT:
				{
					//char temp[1024];
					char* pRichEditText = NULL;
					long nChar = 0;
					CHARRANGE chRange = {0,0};
					BOOL bMimeMessage = FALSE;
					BOOL bDecryptSuccessful = FALSE;
					BOOL bToggle = FALSE;
					BOOL bSelectedText = FALSE;
					FINDTEXT ftEncrypted;
					FINDTEXT ftSigned;
					long nCharPos = 0;
					HCURSOR hCursor, hOldCursor;
					BOOL FYEO;

					// Find the windows we are interested in...
					hwndParent = GetParent(hwnd);
					hwndRichEdit = FindWindowEx(hwndParent, 
												NULL, 
												"RICHEDIT", 
												NULL);

					// Is the control in Edit Mode
					bToggle = !SendMessage(hwnd, TB_ISBUTTONCHECKED, 34002, 0);

					// See if the user has selected text in the window
					SendMessage(hwndRichEdit,  
								EM_EXGETSEL, 
								(WPARAM)0,
								(LPARAM) 
								&chRange);

					bSelectedText = chRange.cpMax - chRange.cpMin;

					// Prepare to look for our plug-ins
					// Mime Encrypted Text
					ftEncrypted.lpstrText = "<0880.0001>"; // Search String
					ftEncrypted.chrg.cpMin = 0;
					ftEncrypted.chrg.cpMax = -1; // All Text

					// Mime Signed Text
					ftSigned.lpstrText = "<0880.0002>"; // Search String
					ftSigned.chrg.cpMin = 0;
					ftSigned.chrg.cpMax = -1; // All Text
					
					// Lock window so we do not flash
					//LockWindowUpdate( hwndRichEdit ); 

					// if not in edit mode place us there
					if(bToggle)
					{
						SendMessage(hwndParent, WM_COMMAND, 34002, 0);
						SendMessage(hwnd, 
									TB_CHECKBUTTON, 
									34002, 
									MAKELONG(TRUE, 0));
					}

					// This could take awhile... give some feedback.

					hCursor = LoadCursor(NULL, IDC_WAIT);
					hOldCursor = SetCursor(hCursor);

					// get text of message
					pRichEditText = GetRichEditContents (	hwndRichEdit, 
															&nChar, 
															FALSE, 
															bSelectedText);
					
					if(!bSelectedText)
					{
						// see if our mime encrypted text plugin is there
						nCharPos = SendMessage(	hwndRichEdit, 
												EM_FINDTEXT, 
												0,(LPARAM) 
												&ftEncrypted);

						if( nCharPos == -1 )
						{
							// if not see if our mime signed text plugin is 
							// there
							nCharPos = SendMessage(	hwndRichEdit, 
													EM_FINDTEXT, 
													0,
													(LPARAM) &ftSigned);
						}

						// if one of them are there "click" on the plugin
						if( nCharPos != -1 )
						{
							POINT pt;

							//MessageBox(NULL, "Click!!", "Decrypt", MB_OK);

							bMimeMessage = TRUE;

							SendMessage(hwndRichEdit, 
								EM_POSFROMCHAR, 
								(WPARAM) &pt,
								(LPARAM) nCharPos);

							SendMessage(hwndRichEdit, 
								WM_LBUTTONDOWN, 
								MK_LBUTTON, 
								MAKELPARAM(pt.x + 2, pt.y + 2));

							SendMessage(hwndRichEdit, 
								WM_LBUTTONUP, 
								MK_LBUTTON, 
								MAKELPARAM(pt.x + 2, pt.y + 2));

							SendMessage(hwndRichEdit, 
								WM_LBUTTONDBLCLK, 
								MK_LBUTTON, 
								MAKELPARAM(pt.x + 2, pt.y + 2));
						}
						else
						{
							// if we were not in edit mode take ourselves 
							// out of edit mode
							if(bToggle)
							{
								SendMessage(hwndParent, WM_COMMAND, 34002, 0);
								SendMessage(hwnd, 
									TB_CHECKBUTTON, 
									34002, 
									MAKELONG(FALSE, 0));
							}
						}
					}

					// Let the window update itself
					//LockWindowUpdate( NULL ); 

					// if it was not a mime message then see if there is 
					// any "classic" pgp text
					if( !bMimeMessage && pRichEditText )//<0880.0004>
					{
						// Decrypt Text
						bDecryptSuccessful = DecryptVerifyRichEditText(
												&pRichEditText, 
												&nChar, &FYEO);

						if( bDecryptSuccessful )
						{
							// put it in edit mode so they have to explicitly 
							// save it as cleartext
							// if there was a MIME message we are already in 
							// edit mode

							if((FYEO)||(GetSecureViewerPref(g_pgpContext)))
							{
								TempestViewer((void *)g_pgpContext,hwnd,
									pRichEditText,nChar,FYEO);
							}
							else
							{
								if(bToggle && !bMimeMessage)
								{
									SendMessage(hwndParent, 
										WM_COMMAND, 
										34002, 
										0);
									SendMessage(hwnd, 
										TB_CHECKBUTTON, 
										34002, 
										MAKELONG(TRUE, 0));
								}

								SetRichEditContents (hwndRichEdit, 
									pRichEditText,
									FALSE, 
									bSelectedText);
							
							//MessageBox(NULL, "huh?", "Decrypt", MB_OK);
							}
						}
					}

					if( pRichEditText )
					{
						// clean up after ourselves
						HeapFree(GetProcessHeap(), 0, pRichEditText);
					}

					SetCursor(hOldCursor);
					break;
				}

				case IDC_KEYMGR:
				{
					char szPath[MAX_PATH];
					char szPGPkeys[256];
					PGPError error = kPGPError_NoErr;

					LoadString(g_hinst, IDS_PGPKEYSEXE, szPGPkeys,
						sizeof(szPGPkeys));

					error = PGPclGetPGPPath (szPath, sizeof(szPath));

					if( IsntPGPError(error) )
					{
						// '/s' keeps it from showing that 
						// damn splash screen
						strcat(szPath, szPGPkeys);
						// run it...
						WinExec(szPath, SW_SHOW);
					}
					else
					{
						char szError[256];

						LoadString(g_hinst, IDS_E_LAUNCHPGPKEYS, szError,
							sizeof(szError));

						MessageBox(NULL, 
							szError, 
							0, 
							MB_OK);
					}
					
					break;
				}
			}
		}
	} 
	
	//  Pass all non-custom messages to old window proc
	return CallWindowProc(lpOldProc, hwnd, msg, wParam, lParam ) ;
}