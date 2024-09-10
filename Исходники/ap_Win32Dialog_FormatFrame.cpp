BOOL AP_Win32Dialog_FormatFrame::_onCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	WORD wNotifyCode = HIWORD(wParam);
	WORD wId = LOWORD(wParam);

	switch (wId)
	{			
		case AP_RID_DIALOG_FORMATFRAME_BMP_BOTTOM:		
		{
			bool bChecked;			
			bChecked = (bool)(IsDlgButtonChecked(m_hDlg, AP_RID_DIALOG_FORMATFRAME_BMP_BOTTOM)==BST_CHECKED);							
			toggleLineType(AP_Dialog_FormatFrame::toggle_bottom, bChecked);				
			event_previewExposed();			
			return 1;
		}			
		
		case AP_RID_DIALOG_FORMATFRAME_BMP_TOP:		
		{
			bool bChecked;			
			bChecked = (bool)(IsDlgButtonChecked(m_hDlg, AP_RID_DIALOG_FORMATFRAME_BMP_TOP)==BST_CHECKED);							
			toggleLineType(AP_Dialog_FormatFrame::toggle_top, bChecked);				
			event_previewExposed();			
			return 1;
		}	
		
		case AP_RID_DIALOG_FORMATFRAME_BMP_RIGHT:		
		{
			bool bChecked;			
			bChecked = (bool)(IsDlgButtonChecked(m_hDlg, AP_RID_DIALOG_FORMATFRAME_BMP_RIGHT)==BST_CHECKED);							
			toggleLineType(AP_Dialog_FormatFrame::toggle_right, bChecked);				
			event_previewExposed();			
			return 1;
		}			
		
		case AP_RID_DIALOG_FORMATFRAME_BMP_LEFT:		
		{
			bool bChecked;			
			bChecked = (bool)(IsDlgButtonChecked(m_hDlg, AP_RID_DIALOG_FORMATFRAME_BMP_LEFT)==BST_CHECKED);							
			toggleLineType(AP_Dialog_FormatFrame::toggle_left, bChecked);				
			event_previewExposed();			
			return 1;
		}	
		 
		 
		case AP_RID_DIALOG_FORMATFRAME_BTN_BORDERCOLOR:		
		{	
			CHOOSECOLORW cc;                
			static COLORREF acrCustClr[16];
			
			/* Initialize CHOOSECOLOR */
			ZeroMemory(&cc, sizeof(CHOOSECOLORW));
			cc.lStructSize = sizeof(CHOOSECOLORW);
			cc.hwndOwner = m_hDlg;
			cc.lpCustColors = (LPDWORD) acrCustClr;
			cc.rgbResult = 0;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		 
			if(ChooseColorW(&cc))			
			{
				setBorderColor(UT_RGBColor(GetRValue( cc.rgbResult), GetGValue(cc.rgbResult), GetBValue(cc.rgbResult)));		
				m_borderButton.setColour(cc.rgbResult);

				/*Force redraw*/
				InvalidateRect(GetDlgItem(hWnd, AP_RID_DIALOG_FORMATFRAME_BTN_BORDERCOLOR), NULL, FALSE);
				event_previewExposed();	
			}

			return 1;
		}	
		
		
		case AP_RID_DIALOG_FORMATFRAME_BTN_BACKCOLOR:		
		{	
			CHOOSECOLORW cc;               
			static COLORREF acrCustClr2[16];
			
			/* Initialize CHOOSECOLOR */
			ZeroMemory(&cc, sizeof(CHOOSECOLORW));
			cc.lStructSize = sizeof(CHOOSECOLORW);
			cc.hwndOwner = m_hDlg;
			cc.lpCustColors = (LPDWORD) acrCustClr2;
			cc.rgbResult = 0;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		 
			if(ChooseColorW(&cc))			
			{
				setBGColor(UT_RGBColor(GetRValue( cc.rgbResult), GetGValue(cc.rgbResult), GetBValue(cc.rgbResult)));						
				m_backgButton.setColour(cc.rgbResult);

				/*Force redraw*/
				InvalidateRect(GetDlgItem(hWnd, AP_RID_DIALOG_FORMATFRAME_BTN_BACKCOLOR), NULL, FALSE);
				event_previewExposed();	
			}

			return 1;
		}			

		case AP_RID_DIALOG_FORMATFRAME_CHK_TEXTWRAP:
		{
			bool bChecked;
			bChecked = (bool)(IsDlgButtonChecked(m_hDlg, AP_RID_DIALOG_FORMATFRAME_CHK_TEXTWRAP)==BST_CHECKED);

			setWrapping(bChecked);

			// Not necessary now, but we may some day show
			// text wrapping in the preview.
			event_previewExposed();
			return 1;
		}

			
		case AP_RID_DIALOG_FORMATFRAME_BTN_CANCEL:			
			m_answer = AP_Dialog_FormatFrame::a_CLOSE;
			destroy();
			event_Close();
			EndDialog(hWnd,0);
			return 1;

		case AP_RID_DIALOG_FORMATFRAME_COMBO_THICKNESS:
		{
			if (wNotifyCode == CBN_SELCHANGE)                       
			{
				int nSelected = getComboSelectedIndex (AP_RID_DIALOG_FORMATFRAME_COMBO_THICKNESS);

				if (nSelected != CB_ERR)
				{
					UT_LocaleTransactor t(LC_NUMERIC, "C");					
					UT_Win32LocaleString thickness;
					UT_UTF8String thickness_utf8 = thickness.utf8_str ();
					getComboTextItem(AP_RID_DIALOG_FORMATFRAME_COMBO_THICKNESS, nSelected, thickness);
					setBorderThicknessAll(thickness_utf8);					
					event_previewExposed();
				}
			}
			return 1;
		}

		case AP_RID_DIALOG_FORMATFRAME_BUTTON_SELIMAGE:
				askForGraphicPathName();
				return 1;

		case AP_RID_DIALOG_FORMATFRAME_BUTTON_NOIMAGE:
				clearImage();
				return 1;

		case AP_RID_DIALOG_FORMATFRAME_RADIO_PARA:
				setPositionMode(FL_FRAME_POSITIONED_TO_BLOCK);
				return 1;

		case AP_RID_DIALOG_FORMATFRAME_RADIO_COLUMN:
				setPositionMode(FL_FRAME_POSITIONED_TO_COLUMN);
				return 1;

		case AP_RID_DIALOG_FORMATFRAME_RADIO_PAGE:
				setPositionMode(FL_FRAME_POSITIONED_TO_PAGE);
				return 1;

		case AP_RID_DIALOG_FORMATFRAME_BTN_APPLY:
				applyChanges();
				return 1;

		
			
		default:							// we did not handle this notification 
			UT_DEBUGMSG(("WM_Command for id %ld\n",wId));
			return 0;						// return zero to let windows take care of it.
	}
}