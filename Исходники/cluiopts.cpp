INT_PTR CALLBACK cfg::DlgProcCluiOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_INITDIALOG:
		{
            opt_clui_changed = 0;
			TranslateDialogDefault(hwndDlg);
			CheckDlgButton(hwndDlg, IDC_BRINGTOFRONT, cfg::getByte("CList", "BringToFront", SETTING_BRINGTOFRONT_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_ALWAYSHIDEONTASKBAR, cfg::getByte("CList", "AlwaysHideOnTB", 1) ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_ONTOP, cfg::getByte("CList", "OnTop", SETTING_ONTOP_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_CLIENTDRAG, cfg::getByte("CLUI", "ClientAreaDrag", SETTING_CLIENTDRAG_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_FADEINOUT, cfg::dat.fadeinout ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_AUTOSIZE, cfg::dat.autosize);
			CheckDlgButton(hwndDlg, IDC_ONDESKTOP, cfg::getByte("CList", "OnDesktop", 0) ? BST_CHECKED : BST_UNCHECKED);

			SendDlgItemMessage(hwndDlg, IDC_MAXSIZESPIN, UDM_SETRANGE, 0, MAKELONG(100, 0));
			SendDlgItemMessage(hwndDlg, IDC_MAXSIZESPIN, UDM_SETPOS, 0, cfg::getByte("CLUI", "MaxSizeHeight", 75));

			SendDlgItemMessage(hwndDlg, IDC_CLUIFRAMESBDR, CPM_SETCOLOUR, 0, cfg::getDword("CLUI", "clr_frameborder", RGB(40, 40, 40)));

			CheckDlgButton(hwndDlg, IDC_AUTOSIZEUPWARD, cfg::getByte("CLUI", "AutoSizeUpward", 0) ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_AUTOHIDE, cfg::getByte("CList", "AutoHide", SETTING_AUTOHIDE_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
			SendDlgItemMessage(hwndDlg, IDC_HIDETIMESPIN, UDM_SETRANGE, 0, MAKELONG(900, 1));
			SendDlgItemMessage(hwndDlg, IDC_HIDETIMESPIN, UDM_SETPOS, 0, MAKELONG(cfg::getWord("CList", "HideTime", SETTING_HIDETIME_DEFAULT), 0));
			Utils::enableDlgControl(hwndDlg, IDC_HIDETIME, IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
			Utils::enableDlgControl(hwndDlg, IDC_HIDETIMESPIN, IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
			Utils::enableDlgControl(hwndDlg, IDC_STATIC01, IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
			if (!IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE)) {
				Utils::enableDlgControl(hwndDlg, IDC_STATIC21, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_STATIC22, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_MAXSIZEHEIGHT, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_MAXSIZESPIN, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_AUTOSIZEUPWARD, FALSE);
			}
			CheckDlgButton(hwndDlg, IDC_TRANSPARENT, cfg::dat.isTransparent ? BST_CHECKED : BST_UNCHECKED);
			if (!IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT)) {
				Utils::enableDlgControl(hwndDlg, IDC_STATIC11, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_STATIC12, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_TRANSACTIVE, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_TRANSINACTIVE, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_ACTIVEPERC, FALSE);
				Utils::enableDlgControl(hwndDlg, IDC_INACTIVEPERC, FALSE);
			}
			SendDlgItemMessage(hwndDlg, IDC_TRANSACTIVE, TBM_SETRANGE, FALSE, MAKELONG(1, 255));
			SendDlgItemMessage(hwndDlg, IDC_TRANSINACTIVE, TBM_SETRANGE, FALSE, MAKELONG(1, 255));
			SendDlgItemMessage(hwndDlg, IDC_TRANSACTIVE, TBM_SETPOS, TRUE, cfg::dat.alpha);
			SendDlgItemMessage(hwndDlg, IDC_TRANSINACTIVE, TBM_SETPOS, TRUE, cfg::dat.autoalpha);
			SendMessage(hwndDlg, WM_HSCROLL, 0x12345678, 0);

			CheckDlgButton(hwndDlg, IDC_USEAERO, Skin::settings.fUseAero ? BST_CHECKED : BST_UNCHECKED);
			SendDlgItemMessage(hwndDlg, IDC_FRAMEGAPSPIN, UDM_SETRANGE, 0, MAKELONG(10, 0));
			SendDlgItemMessage(hwndDlg, IDC_FRAMEGAPSPIN, UDM_SETPOS, 0, (LPARAM)cfg::dat.gapBetweenFrames);

			return TRUE;
		}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_AUTOHIDE) {
			Utils::enableDlgControl(hwndDlg, IDC_HIDETIME, IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
			Utils::enableDlgControl(hwndDlg, IDC_HIDETIMESPIN, IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
			Utils::enableDlgControl(hwndDlg, IDC_STATIC01, IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
		} else if (LOWORD(wParam) == IDC_TRANSPARENT) {
			Utils::enableDlgControl(hwndDlg, IDC_STATIC11, IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
			Utils::enableDlgControl(hwndDlg, IDC_STATIC12, IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
			Utils::enableDlgControl(hwndDlg, IDC_TRANSACTIVE, IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
			Utils::enableDlgControl(hwndDlg, IDC_TRANSINACTIVE, IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
			Utils::enableDlgControl(hwndDlg, IDC_ACTIVEPERC, IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
			Utils::enableDlgControl(hwndDlg, IDC_INACTIVEPERC, IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
		} else if (LOWORD(wParam) == IDC_AUTOSIZE) {
			Utils::enableDlgControl(hwndDlg, IDC_STATIC21, IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE));
			Utils::enableDlgControl(hwndDlg, IDC_STATIC22, IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE));
			Utils::enableDlgControl(hwndDlg, IDC_MAXSIZEHEIGHT, IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE));
			Utils::enableDlgControl(hwndDlg, IDC_MAXSIZESPIN, IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE));
			Utils::enableDlgControl(hwndDlg, IDC_AUTOSIZEUPWARD, IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE));
		}
		if ((LOWORD(wParam) == IDC_FRAMEGAP || LOWORD(wParam) == IDC_HIDETIME || LOWORD(wParam) == IDC_ROWGAP ||
			LOWORD(wParam) == IDC_MAXSIZEHEIGHT) && (HIWORD(wParam) != EN_CHANGE || (HWND) lParam != GetFocus()))
			return 0;
		SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
        opt_clui_changed = 1;
		break;

	case WM_HSCROLL:
		{
			char str[10];
			wsprintfA(str, "%d%%", 100 * SendDlgItemMessage(hwndDlg, IDC_TRANSINACTIVE, TBM_GETPOS, 0, 0) / 255);
			SetDlgItemTextA(hwndDlg, IDC_INACTIVEPERC, str);
			wsprintfA(str, "%d%%", 100 * SendDlgItemMessage(hwndDlg, IDC_TRANSACTIVE, TBM_GETPOS, 0, 0) / 255);
			SetDlgItemTextA(hwndDlg, IDC_ACTIVEPERC, str);
		}
		if (wParam != 0x12345678) {
            SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
            opt_clui_changed = 1;
        }
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code) {
		case PSN_APPLY:
			{
				BOOL translated;
				BYTE oldFading;
				COLORREF clr_cluiframes;

                if(!opt_clui_changed)
                    return TRUE;

                cfg::writeByte("CLUI", "FadeInOut", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_FADEINOUT));
				cfg::dat.fadeinout = IsDlgButtonChecked(hwndDlg, IDC_FADEINOUT) ? 1 : 0;
				oldFading = cfg::dat.fadeinout;
				cfg::dat.fadeinout = FALSE;

				cfg::dat.gapBetweenFrames = GetDlgItemInt(hwndDlg, IDC_FRAMEGAP, &translated, FALSE);

				cfg::writeDword("CLUIFrames", "GapBetweenFrames", cfg::dat.gapBetweenFrames);
				cfg::writeByte("CList", "OnTop", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_ONTOP));
				SetWindowPos(pcli->hwndContactList, IsDlgButtonChecked(hwndDlg, IDC_ONTOP) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

				SendMessage(pcli->hwndContactList, WM_SIZE, 0, 0);

				cfg::writeByte("CList", "BringToFront", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_BRINGTOFRONT));
				cfg::writeByte("CList", "AlwaysHideOnTB", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_ALWAYSHIDEONTASKBAR));

				cfg::writeDword("CLUI", "Frameflags", cfg::dat.dwFlags);

				cfg::writeByte("CLUI", "ClientAreaDrag", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_CLIENTDRAG));

				clr_cluiframes = (COLORREF)SendDlgItemMessage(hwndDlg, IDC_CLUIFRAMESBDR, CPM_GETCOLOUR, 0, 0);

				if(CLUI::hPenFrames)
					DeleteObject(CLUI::hPenFrames);
				CLUI::hPenFrames = CreatePen(PS_SOLID, 1, clr_cluiframes);
				cfg::writeDword("CLUI", "clr_frameborder", clr_cluiframes);

				CLUI::applyBorderStyle();

				cfg::writeByte("CLUI", "AutoSize", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE));

				if((cfg::dat.autosize = IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZE) ? 1 : 0)) {
					SendMessage(pcli->hwndContactList, WM_SIZE, 0, 0);
					SendMessage(pcli->hwndContactTree, WM_SIZE, 0, 0);
				}

				cfg::writeByte("CLUI", "MaxSizeHeight", (BYTE) GetDlgItemInt(hwndDlg, IDC_MAXSIZEHEIGHT, NULL, FALSE));
				cfg::writeByte("CLUI", "AutoSizeUpward", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_AUTOSIZEUPWARD));
				cfg::writeByte("CList", "AutoHide", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_AUTOHIDE));
				cfg::writeWord("CList", "HideTime", (WORD) SendDlgItemMessage(hwndDlg, IDC_HIDETIMESPIN, UDM_GETPOS, 0, 0));

				cfg::writeByte("CList", "Transparent", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT));
				cfg::dat.isTransparent = IsDlgButtonChecked(hwndDlg, IDC_TRANSPARENT) ? 1 : 0;
				cfg::writeByte("CList", "Alpha", (BYTE) SendDlgItemMessage(hwndDlg, IDC_TRANSACTIVE, TBM_GETPOS, 0, 0));
				cfg::dat.alpha = (BYTE) SendDlgItemMessage(hwndDlg, IDC_TRANSACTIVE, TBM_GETPOS, 0, 0);
				cfg::writeByte("CList", "AutoAlpha", (BYTE) SendDlgItemMessage(hwndDlg, IDC_TRANSINACTIVE, TBM_GETPOS, 0, 0));
				cfg::dat.autoalpha = (BYTE) SendDlgItemMessage(hwndDlg, IDC_TRANSINACTIVE, TBM_GETPOS, 0, 0);
				cfg::writeByte("CList", "OnDesktop", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_ONDESKTOP));
				cfg::writeDword("CLUI", "Frameflags", cfg::dat.dwFlags);

				cfg::writeByte(SKIN_DB_MODULE, "sfUseAero", IsDlgButtonChecked(hwndDlg, IDC_USEAERO));
				if(g_CLUISkinnedBkColorRGB)
					cfg::dat.colorkey = g_CLUISkinnedBkColorRGB;
				else {
					SendMessage(pcli->hwndContactList, WM_SIZE, 0, 0);
					cfg::dat.colorkey = RGB(255, 0, 255);
				}

				Api::updateState();
				if(!cfg::isAero) {
					if (cfg::dat.isTransparent || Skin::metrics.fHaveColorkey) {
						SetLayeredWindowAttributes(pcli->hwndContactList, 0, 255, LWA_ALPHA | LWA_COLORKEY);
						SetLayeredWindowAttributes(pcli->hwndContactList,
							(COLORREF)(Skin::metrics.fHaveColorkey ? cfg::dat.colorkey : 0),
							(BYTE)(cfg::dat.isTransparent ? cfg::dat.autoalpha : 255),
							(DWORD)((cfg::dat.isTransparent ? LWA_ALPHA : 0L) | (Skin::metrics.fHaveColorkey ? LWA_COLORKEY : 0L)));
					} else
						SetLayeredWindowAttributes(pcli->hwndContactList, RGB(0, 0, 0), (BYTE)255, LWA_ALPHA);
				}
                CLUI::configureGeometry(1);
                ShowWindow(pcli->hwndContactList, SW_SHOW);
                SendMessage(pcli->hwndContactList, WM_SIZE, 0, 0);
                SetWindowPos(pcli->hwndContactList, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
                RedrawWindow(pcli->hwndContactList, NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
				cfg::dat.fadeinout = oldFading;
				SFL_SetState(cfg::dat.bUseFloater & CLUI_FLOATER_AUTOHIDE ? (cfg::getByte("CList", "State", SETTING_STATE_NORMAL) == SETTING_STATE_NORMAL ? 0 : 1) : 1);
                opt_clui_changed = 0;
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}