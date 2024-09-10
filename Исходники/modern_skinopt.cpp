INT_PTR CALLBACK DlgSkinOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch ( msg )
	{
	case WM_DESTROY:
		{
			if ( hPreviewBitmap ) ske_UnloadGlyphImage( hPreviewBitmap );
			break;
		}

	case WM_INITDIALOG:
		{
			TranslateDialogDefault( hwndDlg );
			HTREEITEM it = FillAvailableSkinList( hwndDlg );
			HWND wnd = GetDlgItem( hwndDlg, IDC_TREE1 );
			TreeView_SelectItem( wnd, it );
		}
		return 0;
	case WM_COMMAND:
		{
			int isLoad = 0;
			switch ( LOWORD(wParam )) {
			case IDC_COLOUR_MENUNORMAL:
			case IDC_COLOUR_MENUSELECTED:
			case IDC_COLOUR_FRAMES:
			case IDC_COLOUR_STATUSBAR:
				SendMessage( GetParent( hwndDlg ), PSM_CHANGED, 0, 0 );
				break;

			case IDC_BUTTON_INFO:
				{
					TCHAR Author[255], URL[MAX_PATH], Contact[255], Description[400], text[2000];
					SkinListData *sd = NULL;
					HTREEITEM hti = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE1 ));
					if ( hti == 0 ) return 0;
					{
						TVITEM tvi = {0};
						tvi.hItem = hti;
						tvi.mask = TVIF_HANDLE|TVIF_PARAM;
						TreeView_GetItem( GetDlgItem( hwndDlg, IDC_TREE1 ), &tvi );
						sd = ( SkinListData* )( tvi.lParam);
					}
					if (!sd ) return 0;
					if ( sd->File && !_tcschr( sd->File, _T('%')))
					{
						GetPrivateProfileString( _T("Skin_Description_Section"), _T("Author"), 	TranslateT("( unknown )"), 	Author, 		SIZEOF( Author ), 		sd->File );
						GetPrivateProfileString( _T("Skin_Description_Section"), _T("URL"), 		_T(""), 						URL, 		SIZEOF( URL ), 		sd->File );
						GetPrivateProfileString( _T("Skin_Description_Section"), _T("Contact"), 	_T(""), 						Contact, 	SIZEOF( Contact ), 	sd->File );
						GetPrivateProfileString( _T("Skin_Description_Section"), _T("Description"), _T(""), 					Description, SIZEOF( Description ), sd->File );
						mir_sntprintf(text, SIZEOF(text), TranslateT("%s\n\n%s\n\nAuthor(s):\t %s\nContact:\t %s\nWeb:\t %s\n\nFile:\t %s"),
							sd->Name, Description, Author, Contact, URL, sd->File);
					}
					else
					{
						mir_sntprintf(text, SIZEOF(text), TranslateT("%s\n\n%s\n\nAuthor(s): %s\nContact:\t %s\nWeb:\t %s\n\nFile:\t %s"),
							TranslateT("reVista for Modern v0.5"),
							TranslateT("This is second default Modern Contact list skin in Vista Aero style"),
							TranslateT("Angeli-Ka (graphics), FYR (template)"),
							_T("JID: [email protected]"),
							_T("fyr.mirandaim.ru"),
							TranslateT("Inside library"));
					}
					MessageBox( hwndDlg, text, TranslateT("Skin Information"), MB_OK|MB_ICONINFORMATION );
				}
				break;
			case IDC_BUTTON_APPLY_SKIN:
				if ( HIWORD(wParam ) == BN_CLICKED )
				{
					SkinListData *sd = NULL;
					HTREEITEM hti = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE1 ));
					if ( hti == 0 ) return 0;
					{
						TVITEM tvi = {0};
						tvi.hItem = hti;
						tvi.mask = TVIF_HANDLE|TVIF_PARAM;
						TreeView_GetItem( GetDlgItem( hwndDlg, IDC_TREE1 ), &tvi );
						sd = ( SkinListData* )( tvi.lParam);
					}
					if (!sd ) return 0;
					if ( glSkinWasModified>0 )
					{
						int res = 0;
						if ( glSkinWasModified == 1 )
							res = MessageBox( hwndDlg, TranslateT("Skin editor contains not stored changes.\n\nAll changes will be lost.\n\n Continue to load new skin?"), TranslateT("Warning!"), MB_OKCANCEL|MB_ICONWARNING|MB_DEFBUTTON2|MB_TOPMOST );
						else
							res = MessageBox( hwndDlg, TranslateT("Current skin was not saved to file.\n\nAll changes will be lost.\n\n Continue to load new skin?"), TranslateT("Warning!"), MB_OKCANCEL|MB_ICONWARNING|MB_DEFBUTTON2|MB_TOPMOST );
						if ( res != IDOK ) return 0;
					}
					ske_LoadSkinFromIniFile( sd->File, FALSE );
					ske_LoadSkinFromDB();
					glOtherSkinWasLoaded = TRUE;
					pcli->pfnClcBroadcast( INTM_RELOADOPTIONS, 0, 0 );
					Sync( CLUIFrames_OnClistResize_mod, 0, 0 );
					ske_RedrawCompleteWindow( );
					Sync( CLUIFrames_OnClistResize_mod, 0, 0 );
					{
						HWND hwnd = pcli->hwndContactList;
						RECT rc = {0};
						GetWindowRect( hwnd, &rc );
						Sync( CLUIFrames_OnMoving, hwnd, &rc );
					}
					if ( g_hCLUIOptionsWnd )
					{
						SendDlgItemMessage( g_hCLUIOptionsWnd, IDC_LEFTMARGINSPIN, UDM_SETPOS, 0, db_get_b( NULL, "CLUI", "LeftClientMargin", SETTING_LEFTCLIENTMARIGN_DEFAULT ));
						SendDlgItemMessage( g_hCLUIOptionsWnd, IDC_RIGHTMARGINSPIN, UDM_SETPOS, 0, db_get_b( NULL, "CLUI", "RightClientMargin", SETTING_RIGHTCLIENTMARIGN_DEFAULT ));
						SendDlgItemMessage( g_hCLUIOptionsWnd, IDC_TOPMARGINSPIN, UDM_SETPOS, 0, db_get_b( NULL, "CLUI", "TopClientMargin", SETTING_TOPCLIENTMARIGN_DEFAULT ));
						SendDlgItemMessage( g_hCLUIOptionsWnd, IDC_BOTTOMMARGINSPIN, UDM_SETPOS, 0, db_get_b( NULL, "CLUI", "BottomClientMargin", SETTING_BOTTOMCLIENTMARIGN_DEFAULT ));
					}
				}
				break;
			case IDC_BUTTON_RESCAN:
				if (HIWORD(wParam ) == BN_CLICKED)
				{
					HTREEITEM it = FillAvailableSkinList(hwndDlg);
					HWND wnd = GetDlgItem(hwndDlg, IDC_TREE1);
					TreeView_SelectItem(wnd, it);
				}
			}
			break;
		}
	case WM_DRAWITEM:
		if ( wParam == IDC_PREVIEW )
		{
			//TODO:Draw hPreviewBitmap here
			int mWidth, mHeight;
			HBRUSH hbr = CreateSolidBrush( GetSysColor( COLOR_3DFACE ));
			DRAWITEMSTRUCT *dis = ( DRAWITEMSTRUCT * )lParam;
			mWidth = dis->rcItem.right-dis->rcItem.left;
			mHeight = dis->rcItem.bottom-dis->rcItem.top;
			HDC memDC = CreateCompatibleDC( dis->hDC );
			HBITMAP hbmp = ske_CreateDIB32( mWidth, mHeight );
			HBITMAP holdbmp = ( HBITMAP )SelectObject( memDC, hbmp );
			RECT workRect = dis->rcItem;
			OffsetRect( &workRect, -workRect.left, -workRect.top );
			FillRect( memDC, &workRect, hbr );
			DeleteObject( hbr );
			if ( hPreviewBitmap )
			{
				//variables
				BITMAP bmp = {0};
				POINT imgPos = {0};
				float xScale = 1, yScale = 1;
				//GetSize
				GetObject( hPreviewBitmap, sizeof( BITMAP ), &bmp );
				int wWidth = workRect.right-workRect.left;
				int wHeight = workRect.bottom-workRect.top;
				if ( wWidth < bmp.bmWidth ) xScale = ( float )wWidth/bmp.bmWidth;
				if ( wHeight < bmp.bmHeight ) yScale = ( float )wHeight/bmp.bmHeight;
				xScale = min( xScale, yScale );
				yScale = xScale;
				int dWidth = ( int )( xScale*bmp.bmWidth );
				int dHeight = ( int )( yScale*bmp.bmHeight );
				//CalcPosition
				imgPos.x = workRect.left+(( wWidth-dWidth )>>1 );
				imgPos.y = workRect.top+(( wHeight-dHeight )>>1 );
				//DrawImage
				DrawAvatarImageWithGDIp( memDC, imgPos.x, imgPos.y, dWidth, dHeight, hPreviewBitmap, 0, 0, bmp.bmWidth, bmp.bmHeight, 8, 255 );
			}
			BitBlt( dis->hDC, dis->rcItem.left, dis->rcItem.top, mWidth, mHeight, memDC, 0, 0, SRCCOPY );
			SelectObject( memDC, holdbmp );
			DeleteObject( hbmp );
			DeleteDC( memDC );
		}
		break;

	case WM_NOTIFY:
		switch (( ( LPNMHDR )lParam)->idFrom ) {
		case IDC_TREE1:
			{
				NMTREEVIEW * nmtv = ( NMTREEVIEW * ) lParam;
				if (nmtv == NULL)
					return 0;

				if (nmtv->hdr.code == TVN_SELCHANGEDA || nmtv->hdr.code == TVN_SELCHANGEDW) {
					SkinListData * sd = NULL;
					if (hPreviewBitmap) {
						ske_UnloadGlyphImage( hPreviewBitmap );
						hPreviewBitmap = NULL;
					}

					if (nmtv->itemNew.lParam) {
						sd = ( SkinListData* )nmtv->itemNew.lParam;

						TCHAR buf[MAX_PATH];
						PathToRelativeT(sd->File, buf);
						SetDlgItemText(hwndDlg,IDC_EDIT_SKIN_FILENAME,buf);

						TCHAR prfn[MAX_PATH] = {0}, imfn[MAX_PATH] = {0}, skinfolder[MAX_PATH] = {0};
						GetPrivateProfileString( _T("Skin_Description_Section"), _T("Preview"), _T(""), imfn, SIZEOF( imfn ), sd->File );
						IniParser::GetSkinFolder( sd->File, skinfolder );
						mir_sntprintf(prfn, SIZEOF(prfn), _T("%s\\%s"), skinfolder, imfn);
						PathToAbsoluteT(prfn, imfn);
						hPreviewBitmap = ske_LoadGlyphImage(imfn);

						EnableWindow( GetDlgItem( hwndDlg, IDC_BUTTON_APPLY_SKIN ), TRUE );
						EnableWindow( GetDlgItem( hwndDlg, IDC_BUTTON_INFO ), TRUE );
						if ( hPreviewBitmap )
							InvalidateRect( GetDlgItem( hwndDlg, IDC_PREVIEW ), NULL, TRUE );
						else { //prepare text
							TCHAR Author[255], URL[MAX_PATH], Contact[255], Description[400], text[2000];
							SkinListData* sd = NULL;
							HTREEITEM hti = TreeView_GetSelection( GetDlgItem( hwndDlg, IDC_TREE1 ));
							if ( hti == 0 ) return 0;
							{
								TVITEM tvi = {0};
								tvi.hItem = hti;
								tvi.mask = TVIF_HANDLE|TVIF_PARAM;
								TreeView_GetItem( GetDlgItem( hwndDlg, IDC_TREE1 ), &tvi );
								sd = ( SkinListData* )( tvi.lParam);
							}
							if (!sd ) return 0;

							if ( sd->File && !_tcschr( sd->File, _T('%')))
							{
								GetPrivateProfileString( _T("Skin_Description_Section"), _T("Author"), 	TranslateT("( unknown )"), 	Author, 		SIZEOF( Author ), 		sd->File );
								GetPrivateProfileString( _T("Skin_Description_Section"), _T("URL"), 		_T(""), 						URL, 		SIZEOF( URL ), 		sd->File );
								GetPrivateProfileString( _T("Skin_Description_Section"), _T("Contact"), 	_T(""), 						Contact, 	SIZEOF( Contact ), 	sd->File );
								GetPrivateProfileString( _T("Skin_Description_Section"), _T("Description"), _T(""), 					Description, SIZEOF( Description ), sd->File );
								mir_sntprintf(text, SIZEOF(text), TranslateT("Preview is not available\n\n%s\n----------------------\n\n%s\n\nAUTHOR(S):\n%s\n\nCONTACT:\n%s\n\nHOMEPAGE:\n%s"),
									sd->Name, Description, Author, Contact, URL);
							}
							else
							{
								mir_sntprintf(text, SIZEOF(text), TranslateT("%s\n\n%s\n\nAUTHORS:\n%s\n\nCONTACT:\n%s\n\nWEB:\n%s\n\n\n"),
									TranslateT("reVista for Modern v0.5"),
									TranslateT("This is second default Modern Contact list skin in Vista Aero style"),
									TranslateT("graphics by Angeli-Ka\ntemplate by FYR"),
									_T("JID: [email protected]"),
									_T("fyr.mirandaim.ru"));
							}
							ShowWindow( GetDlgItem( hwndDlg, IDC_PREVIEW ), SW_HIDE );
							ShowWindow( GetDlgItem( hwndDlg, IDC_STATIC_INFO ), SW_SHOW );
							SetDlgItemText(hwndDlg, IDC_STATIC_INFO, text);
						}
					}
					else {
						//no selected
						SetDlgItemText(hwndDlg, IDC_EDIT_SKIN_FILENAME, TranslateT("Select skin from list"));
						EnableWindow( GetDlgItem( hwndDlg, IDC_BUTTON_APPLY_SKIN ), FALSE );
						EnableWindow( GetDlgItem( hwndDlg, IDC_BUTTON_INFO ), FALSE );
						SetDlgItemText(hwndDlg, IDC_STATIC_INFO, TranslateT("Please select skin to apply"));
						ShowWindow( GetDlgItem( hwndDlg, IDC_PREVIEW ), SW_HIDE );
					}
					ShowWindow( GetDlgItem( hwndDlg, IDC_PREVIEW ), hPreviewBitmap?SW_SHOW:SW_HIDE );
					return 0;
				}
				else if (nmtv->hdr.code == TVN_DELETEITEMA || nmtv->hdr.code == TVN_DELETEITEMW) {
					mir_free_and_nil( nmtv->itemOld.lParam);
					return 0;
				}
			}
			break;

		case 0:
			switch (((LPNMHDR)lParam)->code) {
			case PSN_APPLY:
				pcli->pfnClcBroadcast( INTM_RELOADOPTIONS, 0, 0 );
				NotifyEventHooks( g_CluiData.hEventBkgrChanged, 0, 0 );
				pcli->pfnClcBroadcast( INTM_INVALIDATE, 0, 0 );
				RedrawWindow( GetParent( pcli->hwndContactTree ), NULL, NULL, RDW_INVALIDATE|RDW_FRAME|RDW_ALLCHILDREN );
			}
			break;
		}
	}