static BOOL CALLBACK SpectrumPopupProc(HWND wnd,UINT msg,WPARAM wp,LPARAM lp)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		uSetWindowLong(wnd,DWL_USER,lp);
		{
			spec_param * ptr = reinterpret_cast<spec_param*>(lp);
			ptr->m_scope.initialize(FindOwningPopup(wnd));
			uSendDlgItemMessage(wnd, IDC_BARS, BM_SETCHECK, ptr->ptr->mode == MODE_BARS, 0);
			HWND wnd_combo = GetDlgItem(wnd, IDC_FRAME_COMBO);
			EnableWindow(wnd_combo, ptr->b_show_frame);
			if (ptr->b_show_frame)
			{
				ComboBox_AddString(wnd_combo, _T("None"));
				ComboBox_AddString(wnd_combo, _T("Sunken"));
				ComboBox_AddString(wnd_combo, _T("Grey"));
				ComboBox_SetCurSel(wnd_combo, ptr->frame);
			}
			wnd_combo = GetDlgItem(wnd, IDC_SCALE);
			ComboBox_AddString(wnd_combo, _T("Linear"));
			ComboBox_AddString(wnd_combo, _T("Logarithmic"));
			ComboBox_SetCurSel(wnd_combo, ptr->m_scale);

			wnd_combo = GetDlgItem(wnd, IDC_VERTICAL_SCALE);
			ComboBox_AddString(wnd_combo, _T("Linear"));
			ComboBox_AddString(wnd_combo, _T("Logarithmic"));
			ComboBox_SetCurSel(wnd_combo, ptr->m_vertical_scale);
		}
		return TRUE;
	case WM_ERASEBKGND:
		SetWindowLongPtr(wnd, DWL_MSGRESULT, TRUE);
		return TRUE;
	case WM_PAINT:
		ui_helpers::innerWMPaintModernBackground(wnd, GetDlgItem(wnd, IDOK));
		return TRUE;
	case WM_CTLCOLORSTATIC:
		{
			spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
			if (GetDlgItem(wnd, IDC_PATCH_FORE) == (HWND)lp) {
				HDC dc =(HDC)wp;
				if (!ptr->br_fore) 
				{
					ptr->br_fore = CreateSolidBrush(ptr->cr_fore);
				}
				return (BOOL)ptr->br_fore;
			} 
			else if (GetDlgItem(wnd, IDC_PATCH_BACK) == (HWND)lp) 
			{
				HDC dc =(HDC)wp;
				if (!ptr->br_back) 
				{
					ptr->br_back = CreateSolidBrush(ptr->cr_back);
				}
				return (BOOL)ptr->br_back;
			}
			else
			return (BOOL)GetSysColorBrush(COLOR_3DHIGHLIGHT);
		}
		break;
	case WM_COMMAND:
		switch(wp)
		{
		case IDCANCEL:
			EndDialog(wnd,0);
			return TRUE;
		case IDC_CHANGE_BACK:
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				COLORREF COLOR = ptr->cr_back;
				COLORREF COLORS[16] = {get_default_colour(colours::COLOUR_BACK),GetSysColor(COLOR_3DFACE),0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (uChooseColor(&COLOR, wnd, &COLORS[0]))
				{
					ptr->cr_back = COLOR;
					ptr->flush_back();
					RedrawWindow(GetDlgItem(wnd, IDC_PATCH_BACK), 0, 0, RDW_INVALIDATE|RDW_UPDATENOW);
				}
			}
			break;
		case IDC_CHANGE_FORE:
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				COLORREF COLOR = ptr->cr_fore;
				COLORREF COLORS[16] = {get_default_colour(colours::COLOUR_TEXT),GetSysColor(COLOR_3DSHADOW),0,0,0,0,0,0,0,0,0,0,0,0,0,0};
				if (uChooseColor(&COLOR, wnd, &COLORS[0]))
				{
					ptr->cr_fore = COLOR;
					ptr->flush_fore();
					RedrawWindow(GetDlgItem(wnd, IDC_PATCH_FORE), 0, 0, RDW_INVALIDATE|RDW_UPDATENOW);
				}
			}
			break;
		case IDC_BARS:
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				ptr->mode = (uSendMessage((HWND)lp, BM_GETCHECK, 0, 0) != TRUE ? MODE_STANDARD : MODE_BARS);
			}
			break;
		case IDC_FRAME_COMBO|(CBN_SELCHANGE<<16):
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				ptr->frame = ComboBox_GetCurSel(HWND(lp));
			}
			break;
		case IDC_SCALE|(CBN_SELCHANGE<<16):
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				ptr->m_scale = ComboBox_GetCurSel(HWND(lp));
			}
			break;
		case IDC_VERTICAL_SCALE|(CBN_SELCHANGE<<16):
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				ptr->m_vertical_scale = ComboBox_GetCurSel(HWND(lp));
			}
			break;
		case IDOK:
			{
				spec_param * ptr = reinterpret_cast<spec_param*>(uGetWindowLong(wnd,DWL_USER));
				EndDialog(wnd,1);
			}
			return TRUE;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
}