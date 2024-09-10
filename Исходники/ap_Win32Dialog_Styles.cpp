BOOL AP_Win32Dialog_Styles::_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);
	WORD wId = LOWORD(wParam);
	HWND hWndCtrl = (HWND)lParam;

	switch (wId)
	{
	case AP_RID_DIALOG_STYLES_TOP_BUTTON_APPLY:
		{
			const gchar * szStyle = getCurrentStyle();
			if(szStyle && *szStyle)
			{
				getView()->setStyle(szStyle);
			}		
		}
		m_answer = a_OK;
		return 1;

	case AP_RID_DIALOG_STYLES_TOP_BUTTON_CLOSE:
	case IDCANCEL:
		m_answer = a_CANCEL;
		EndDialog(hWnd,0);
		return 1;

	case IDOK:
		{	
     		const XAP_StringSet * pSS = m_pApp->getStringSet ();
			WCHAR stylename[MAX_EBX_LENGTH+1];
			// Verfiy a name value for the style
			// TODO - Verify unique name value
			GetDlgItemTextW(hWnd,AP_RID_DIALOG_STYLES_NEWMODIFY_EBX_NAME,stylename,MAX_EBX_LENGTH);
			/*_win32DialogNewModify.getControlText( AP_RID_DIALOG_STYLES_NEWMODIFY_EBX_NAME,
                                                  m_newStyleName,
	                                              MAX_EBX_LENGTH );*/
			UT_UTF8String str;
			str.appendUCS2((const UT_UCS2Char*)stylename,0);
			strcpy(m_newStyleName,str.utf8_str());

			if( !m_newStyleName || !strlen(m_newStyleName) )
			{
			    getFrame()->showMessageBox( pSS->getValue (AP_STRING_ID_DLG_Styles_ErrBlankName),
											XAP_Dialog_MessageBox::b_O,
											XAP_Dialog_MessageBox::a_OK);

			    return 1;
    		}

			//strcpy (m_newStyleName, (AP_Win32App::s_fromWinLocaleToUTF8(m_newStyleName)).utf8_str());

		}
		m_answer = a_OK;
		EndDialog(hWnd,0);
		return 1;


	case AP_RID_DIALOG_STYLES_TOP_COMBO_LIST:
		if( wNotifyCode == CBN_SELCHANGE )
		{
			switch(_win32Dialog.getComboSelectedIndex(AP_RID_DIALOG_STYLES_TOP_COMBO_LIST))
			{
			case 0:
				m_whichType = USED_STYLES;
				break;
				
			case 1:
				m_whichType = ALL_STYLES;
				break;
				
			case 2:
				m_whichType = USER_STYLES;
				break;
			}

			_populateWindowData();
		}
		return 1;

	case AP_RID_DIALOG_STYLES_TOP_LIST_STYLES:
		if (wNotifyCode == LBN_SELCHANGE)
		{
			
			UT_uint32	nData = -1;
			const char* name;
			const PD_Style * pcStyle = NULL;
			
			int row = _win32Dialog.getListSelectedIndex(AP_RID_DIALOG_STYLES_TOP_LIST_STYLES);					
			
			nData = _win32Dialog.getListDataItem( AP_RID_DIALOG_STYLES_TOP_LIST_STYLES, row);
			
			if (row!=LB_ERR)
			{
				getDoc()->enumStyles(nData, &name, &pcStyle);				
				m_selectedStyle = name; 
				
				m_nSelectedStyleIdx = nData;
							
				// refresh the previews
				_populatePreviews(false);	
			}
			
			break;			
		}
		return 1;

	case AP_RID_DIALOG_STYLES_TOP_BUTTON_DELETE:
		{
			if( m_selectedStyle != "" )
			{
				if ( !getDoc()->removeStyle(m_selectedStyle.c_str()) ) // actually remove the style
				{
					const XAP_StringSet * pSS = m_pApp->getStringSet();
					getFrame()->showMessageBox( pSS->getValue (AP_STRING_ID_DLG_Styles_ErrStyleCantDelete),
												XAP_Dialog_MessageBox::b_O,
												XAP_Dialog_MessageBox::a_OK	);
					return 1;
				}
				getFrame()->repopulateCombos();
				_populateWindowData(); // force a refresh
				getDoc()->signalListeners(PD_SIGNAL_UPDATE_LAYOUT);
				m_selectedStyle = "";
			}
    	}
		return 1;

	case AP_RID_DIALOG_STYLES_TOP_BUTTON_NEW:
		{
			m_bisNewStyle = true;
			//_win32Dialog.showWindow(SW_HIDE);
			XAP_Frame* pFrame = getFrame();
			//_win32DialogNewModify.runModal(pFrame, AP_DIALOG_ID_STYLES, AP_RID_DIALOG_STYLES_NEWMODIFY, this);
			createModal(pFrame, MAKEINTRESOURCEW(AP_RID_DIALOG_STYLES_NEWMODIFY));
			if(m_answer == AP_Dialog_Styles::a_OK)
			{
				createNewStyle((gchar *) m_newStyleName);
				_populateCList();
			}
			destroyAbiPreview();
			DELETEP(m_pAbiPreviewWidget);
			//_win32Dialog.showWindow(SW_SHOW);
		}
		return 1;

	case AP_RID_DIALOG_STYLES_TOP_BUTTON_MODIFY:
		{
			// Verify that a style is selected
			if( m_selectedStyle == "" )
			{
				XAP_Frame * pFrame = getFrame();
				const XAP_StringSet * pSS = m_pApp->getStringSet();
				pFrame->showMessageBox( pSS->getValue(AP_STRING_ID_DLG_Styles_ErrNoStyle),
										XAP_Dialog_MessageBox::b_O,
										XAP_Dialog_MessageBox::a_OK);                                        
				m_answer = AP_Dialog_Styles::a_CANCEL;
				return 1;
			}
			else
			{
				PD_Style * pStyle = NULL;
				getDoc()->getStyle(m_selectedStyle.c_str(), &pStyle);

				m_bisNewStyle = false;
				XAP_Frame* pFrame = getFrame();			
				
				XAP_Win32App * pWin32App = static_cast<XAP_Win32App *>(getApp());
			
				createModal (pFrame, MAKEINTRESOURCEW(AP_RID_DIALOG_STYLES_NEWMODIFY));				
				/*LPCWSTR lpTemplate = MAKEINTRESOURCEW(AP_RID_DIALOG_STYLES_NEWMODIFY);				
											
				int result = DialogBoxParamW(pWin32App->getInstance(), lpTemplate,
									static_cast<XAP_Win32FrameImpl*>(pFrame->getFrameImpl())->getTopLevelWindow(),
									(DLGPROC)s_dlgProc, (LPARAM)this);*/
				
				if(m_answer == AP_Dialog_Styles::a_OK)
				{
					applyModifiedStyleToDoc();
					getDoc()->updateDocForStyleChange(getCurrentStyle(),true);
					getDoc()->signalListeners(PD_SIGNAL_UPDATE_LAYOUT);
				}

				destroyAbiPreview();
				DELETEP(m_pAbiPreviewWidget);
			}
		}
		return 1;

	case AP_RID_DIALOG_STYLES_NEWMODIFY_BTN_REMOVE:
		{
			char szTemp[128];
			_win32DialogNewModify.getControlText( AP_RID_DIALOG_STYLES_NEWMODIFY_CBX_REMOVE,
                                                  szTemp,
	                                              sizeof(szTemp) );			
			removeVecProp(szTemp);
			rebuildDeleteProps();
			updateCurrentStyle();
		}
		return 1;

	case AP_RID_DIALOG_STYLES_NEWMODIFY_BTN_TOGGLEITEMS:
	{
	    RECT 	rect;
	    HMENU 	hMenu;
	    int		x,y;	    	    
	    HWND	hWndButton;
		static int menu_items[]={AP_STRING_ID_DLG_Styles_ModifyParagraph,
								AP_STRING_ID_DLG_Styles_ModifyFont,
								AP_STRING_ID_DLG_Styles_ModifyTabs,
								AP_STRING_ID_DLG_Styles_ModifyNumbering,
								AP_STRING_ID_DLG_Styles_ModifyLanguage
								};
	    
		UT_Win32LocaleString str;

	    hWndButton = GetDlgItem(hWnd, AP_RID_DIALOG_STYLES_NEWMODIFY_BTN_TOGGLEITEMS);
	    XAP_Win32App * app = static_cast<XAP_Win32App *> (m_pApp);		
		const XAP_StringSet * pSS = m_pApp->getStringSet();
	    
		// Get button position
	    GetWindowRect(hWndButton, &rect);
	    x = rect.left;
	    y = rect.bottom;	               		

	    // Menu creation
	    hMenu =  CreatePopupMenu();
		str;
		for (int i=0; i<5; i++) {
			str.fromUTF8(pSS->getValue(menu_items[i]));
			AppendMenuW(hMenu, MF_ENABLED|MF_STRING, i+1, (LPCWSTR)str.c_str());
		}
	
	    // show and track the menu
    	m_selectToggle = TrackPopupMenu(hMenu, TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD,
    						x,y,0, hWndButton,  NULL);		    							    	        						 							    
	    
	    switch(m_selectToggle)
		{
		case 0:	// user has cancelled
			break;
		case 1:
			ModifyParagraph();
			break;
		case 2:
			ModifyFont();
			break;
		case 3:
			ModifyTabs();
			break;
		case 4:
			ModifyLists();
			break;
		case 5:
			ModifyLang();
			break;
		default:
			break;			
		}
		
		rebuildDeleteProps();
		updateCurrentStyle();
	    DestroyMenu(hMenu);
		return 1;
	}


	case AP_RID_DIALOG_STYLES_NEWMODIFY_CBX_BASEDON:
		if( wNotifyCode == CBN_SELCHANGE )
		{
			eventBasedOn();
			rebuildDeleteProps();
		}	
		return 1;

	case AP_RID_DIALOG_STYLES_NEWMODIFY_CBX_FOLLOWPARA:
		if( wNotifyCode == CBN_SELCHANGE )
		{
			eventFollowedBy();
		}	
		return 1;

	case AP_RID_DIALOG_STYLES_NEWMODIFY_CBX_TYPE:
		if( wNotifyCode == CBN_SELCHANGE )
		{
			eventStyleType();
		}
		return 1;

	default:							// we did not handle this notification
		UT_DEBUGMSG(("WM_Command for id %ld\n",wId));
		return 0;						// return zero to let windows take care of it.
	}
	
	return 0;						// return zero to let windows take care of it.
}