int ModernDrawStatusBarWorker(HWND hWnd, HDC hDC)
{
	int iconHeight = GetSystemMetrics(SM_CYSMICON)+2;
	int i;

	// Count visible protos
	RECT rc;
	GetClientRect(hWnd, &rc);
	if (g_CluiData.fDisableSkinEngine) {
		if (g_StatusBarData.bkUseWinColors && xpt_IsThemed(g_StatusBarData.hTheme))
			xpt_DrawTheme(g_StatusBarData.hTheme, hWnd, hDC, 0, 0, &rc, &rc);
		else
			DrawBackGround(hWnd, hDC, g_StatusBarData.hBmpBackground, g_StatusBarData.bkColour, g_StatusBarData.backgroundBmpUse);
	}
	else SkinDrawGlyph(hDC, &rc, &rc, "Main,ID=StatusBar"); //TBD

	g_StatusBarData.nProtosPerLine = db_get_b(NULL, "CLUI", "StatusBarProtosPerLine", SETTING_PROTOSPERLINE_DEFAULT);
	HFONT hOldFont = g_clcPainter.ChangeToFont(hDC, NULL, FONTID_STATUSBAR_PROTONAME, NULL);

	SIZE textSize = { 0 };
	GetTextExtentPoint32A(hDC, " ", 1, &textSize);
	int spaceWidth = textSize.cx;
	int textY = rc.top + ((rc.bottom - rc.top - textSize.cy) >> 1);
	int iconY = rc.top + ((rc.bottom - rc.top - GetSystemMetrics(SM_CXSMICON)) >> 1);

	ProtosData.destroy();

	int protoCount;
	PROTOACCOUNT **accs;
	ProtoEnumAccounts(&protoCount, &accs);
	if (protoCount == 0)
		return 0;

	int iProtoInStatusMenu = 0;
	for (int j = 0; j < protoCount; j++) {
		int i = pcli->pfnGetAccountIndexByPos(j);
		if (i == -1)
			continue;

		char *szProto = accs[i]->szModuleName;
		if (!pcli->pfnGetProtocolVisibility(szProto))
			continue;

		char buf[256];
		mir_snprintf(buf, SIZEOF(buf), "SBarAccountIsCustom_%s", szProto);

		ProtoItemData *p = NULL;

		if (g_StatusBarData.perProtoConfig && db_get_b(NULL, "CLUI", buf, SETTING_SBARACCOUNTISCUSTOM_DEFAULT)) {
			mir_snprintf(buf, SIZEOF(buf), "HideAccount_%s", szProto);
			if (db_get_b(NULL, "CLUI", buf, SETTING_SBARHIDEACCOUNT_DEFAULT)) {
				iProtoInStatusMenu++;
				continue;
			}

			mir_snprintf(buf, SIZEOF(buf), "SBarShow_%s", szProto);

			BYTE showOps = db_get_b(NULL, "CLUI", buf, SETTING_SBARSHOW_DEFAULT);
			p = new ProtoItemData;
			p->bShowProtoIcon = (showOps & 1) != 0;
			p->bShowProtoName = (showOps & 2) != 0;
			p->bShowStatusName = (showOps & 4) != 0;

			mir_snprintf(buf, SIZEOF(buf), "ShowXStatus_%s", szProto);
			p->xStatusMode = db_get_b(NULL, "CLUI", buf, SETTING_SBARSHOW_DEFAULT);

			mir_snprintf(buf, SIZEOF(buf), "UseConnectingIcon_%s", szProto);
			p->bConnectingIcon = db_get_b(NULL, "CLUI", buf, SETTING_USECONNECTINGICON_DEFAULT) != 0;

			mir_snprintf(buf, SIZEOF(buf), "ShowUnreadEmails_%s", szProto);
			p->bShowProtoEmails = db_get_b(NULL, "CLUI", buf, SETTING_SHOWUNREADEMAILS_DEFAULT) != 0;

			mir_snprintf(buf, SIZEOF(buf), "SBarRightClk_%s", szProto);
			p->SBarRightClk = db_get_b(NULL, "CLUI", buf, SETTING_SBARRIGHTCLK_DEFAULT) != 0;

			mir_snprintf(buf, SIZEOF(buf), "PaddingLeft_%s", szProto);
			p->PaddingLeft = db_get_dw(NULL, "CLUI", buf, SETTING_PADDINGLEFT_DEFAULT);

			mir_snprintf(buf, SIZEOF(buf), "PaddingRight_%s", szProto);
			p->PaddingRight = db_get_dw(NULL, "CLUI", buf, SETTING_PADDINGRIGHT_DEFAULT);
		}
		else {
			p = new ProtoItemData;
			p->bShowProtoIcon = g_StatusBarData.bShowProtoIcon;
			p->bShowProtoName = g_StatusBarData.bShowProtoName;
			p->bShowStatusName = g_StatusBarData.bShowStatusName;
			p->xStatusMode = g_StatusBarData.xStatusMode;
			p->bConnectingIcon = g_StatusBarData.bConnectingIcon;
			p->bShowProtoEmails = g_StatusBarData.bShowProtoEmails;
			p->SBarRightClk = 0;
			p->PaddingLeft = 0;
			p->PaddingRight = 0;
		}

		p->iProtoStatus = CallProtoService(szProto, PS_GETSTATUS, 0, 0);

		if (p->iProtoStatus > ID_STATUS_OFFLINE)
			if (p->bShowProtoEmails == 1 && ProtoServiceExists(szProto, PS_GETUNREADEMAILCOUNT)) {
				int nEmails = (int)ProtoCallService(szProto, PS_GETUNREADEMAILCOUNT, 0, 0);
				if (nEmails > 0) {
					char buf[40];
					mir_snprintf(buf, SIZEOF(buf), "[%d]", nEmails);
					p->szProtoEMailCount = mir_strdup(buf);
				}
			}

		p->tszProtoHumanName = mir_tstrdup(accs[i]->tszAccountName);
		p->szAccountName = mir_strdup(szProto);
		p->szProtoName = mir_strdup(accs[i]->szProtoName);
		p->tszProtoStatusText = mir_tstrdup(pcli->pfnGetStatusModeDescription(p->iProtoStatus, 0));
		p->iProtoPos = iProtoInStatusMenu++;

		p->bIsDimmed = 0;
		if (g_CluiData.bFilterEffective & CLVM_FILTER_PROTOS) {
			char szTemp[2048];
			mir_snprintf(szTemp, SIZEOF(szTemp), "%s|", p->szAccountName);
			p->bIsDimmed = strstr(g_CluiData.protoFilter, szTemp) ? 0 : 1;
		}

		ProtosData.insert(p);
	}

	if (ProtosData.getCount() == 0)
		return 0;

	//START MULTILINE HERE 
	int orig_protoCount = protoCount;
	int orig_visProtoCount = ProtosData.getCount();
	int protosperline = 0;

	if (g_StatusBarData.nProtosPerLine)
		protosperline = g_StatusBarData.nProtosPerLine;
	else if (orig_visProtoCount)
		protosperline = orig_visProtoCount;
	else if (protoCount) {
		protosperline = protoCount;
		orig_visProtoCount = protoCount;
	}
	else {
		protosperline = 1;
		orig_visProtoCount = 1;
	}
	protosperline = min(protosperline, orig_visProtoCount);

	int linecount = protosperline ? (orig_visProtoCount + (protosperline - 1)) / protosperline : 1; //divide with rounding to up
	for (int line = 0; line < linecount; line++) {
		int rowheight = max(textSize.cy + 2, iconHeight);
		protoCount = min(protosperline, (orig_protoCount - line*protosperline));
		int visProtoCount = min(protosperline, (orig_visProtoCount - line*protosperline));
		GetClientRect(hWnd, &rc);

		rc.top += g_StatusBarData.rectBorders.top;
		rc.bottom -= g_StatusBarData.rectBorders.bottom;

		int aligndx = 0, maxwidth = 0, xstatus = 0, SumWidth = 0;

		int height = (rowheight*linecount);
		if (height > (rc.bottom - rc.top)) {
			rowheight = (rc.bottom - rc.top) / linecount;
			height = (rowheight*linecount);
		}

		int rowsdy = ((rc.bottom - rc.top) - height) / 2;
		if (rowheight*(line)+rowsdy < rc.top - rowheight) continue;
		if (rowheight*(line + 1) + rowsdy>rc.bottom + rowheight)
			break;

		if (g_StatusBarData.VAlign == 0) { //top
			rc.bottom = rc.top + rowheight*(line + 1);
			rc.top = rc.top + rowheight*line + 1;
		}
		else if (g_StatusBarData.VAlign == 1) { //center
			rc.bottom = rc.top + rowsdy + rowheight*(line + 1);
			rc.top = rc.top + rowsdy + rowheight*line + 1;
		}
		else if (g_StatusBarData.VAlign == 2) { //bottom
			rc.top = rc.bottom - (rowheight*(linecount - line));
			rc.bottom = rc.bottom - (rowheight*(linecount - line - 1) + 1);
		}

		textY = rc.top + (((rc.bottom - rc.top) - textSize.cy) / 2);
		iconY = rc.top + (((rc.bottom - rc.top) - iconHeight) / 2);

		//Code for each line
		DWORD sw;
		int rectwidth = rc.right - rc.left - g_StatusBarData.rectBorders.left - g_StatusBarData.rectBorders.right;
		if (visProtoCount > 1)
			sw = (rectwidth - (g_StatusBarData.extraspace*(visProtoCount - 1))) / visProtoCount;
		else
			sw = rectwidth;

		int *ProtoWidth = (int*)mir_alloc(sizeof(int)*visProtoCount);
		for (i = 0; i < visProtoCount; i++) {
			ProtoItemData &p = ProtosData[line*protosperline + i];

			DWORD w = p.PaddingLeft;
			w += p.PaddingRight;

			if (p.bShowProtoIcon) {
				w += GetSystemMetrics(SM_CXSMICON) + 1;

				p.extraIcon = NULL;
				if ((p.xStatusMode & 8) && p.iProtoStatus > ID_STATUS_OFFLINE) {
					TCHAR str[512];
					CUSTOM_STATUS cs = { sizeof(cs) };
					cs.flags = CSSF_MASK_NAME | CSSF_TCHAR;
					cs.ptszName = str;
					if (CallProtoService(p.szAccountName, PS_GETCUSTOMSTATUSEX, 0, (LPARAM)&cs) == 0)
						p.tszProtoXStatus = mir_tstrdup(str);
				}

				if ((p.xStatusMode & 3)) {
					if (p.iProtoStatus > ID_STATUS_OFFLINE) {
						if (ProtoServiceExists(p.szAccountName, PS_GETCUSTOMSTATUSICON))
							p.extraIcon = (HICON)ProtoCallService(p.szAccountName, PS_GETCUSTOMSTATUSICON, 0, 0);
						if (p.extraIcon && (p.xStatusMode & 3) == 3)
							w += GetSystemMetrics(SM_CXSMICON) + 1;
					}
				}
			}

			SIZE textSize;
			if (p.bShowProtoName) {
				GetTextExtentPoint32(hDC, p.tszProtoHumanName, lstrlen(p.tszProtoHumanName), &textSize);
				w += textSize.cx + 3 + spaceWidth;
			}

			if (p.bShowProtoEmails && p.szProtoEMailCount) {
				GetTextExtentPoint32A(hDC, p.szProtoEMailCount, lstrlenA(p.szProtoEMailCount), &textSize);
				w += textSize.cx + 3 + spaceWidth;
			}

			if (p.bShowStatusName) {
				GetTextExtentPoint32(hDC, p.tszProtoStatusText, lstrlen(p.tszProtoStatusText), &textSize);
				w += textSize.cx + 3 + spaceWidth;
			}

			if ((p.xStatusMode & 8) && p.tszProtoXStatus) {
				GetTextExtentPoint32(hDC, p.tszProtoXStatus, lstrlen(p.tszProtoXStatus), &textSize);
				w += textSize.cx + 3 + spaceWidth;
			}

			if (p.bShowProtoName || (p.bShowProtoEmails && p.szProtoEMailCount) || p.bShowStatusName || ((p.xStatusMode & 8) && p.tszProtoXStatus))
				w -= spaceWidth;

			p.fullWidth = w;
			if (g_StatusBarData.sameWidth) {
				ProtoWidth[i] = sw;
				SumWidth += w;
			}
			else {
				ProtoWidth[i] = w;
				SumWidth += w;
			}
		}

		// Reposition rects
		for (i = 0; i < visProtoCount; i++)
			if (ProtoWidth[i] > maxwidth)
				maxwidth = ProtoWidth[i];

		if (g_StatusBarData.sameWidth) {
			for (i = 0; i < visProtoCount; i++)
				ProtoWidth[i] = maxwidth;
			SumWidth = maxwidth * visProtoCount;
		}
		SumWidth += (visProtoCount - 1) * (g_StatusBarData.extraspace + 1);

		if (SumWidth > rectwidth) {
			float f = (float)rectwidth / SumWidth;
			SumWidth = 0;
			for (i = 0; i < visProtoCount; i++) {
				ProtoWidth[i] = (int)((float)ProtoWidth[i] * f);
				SumWidth += ProtoWidth[i];
			}
			SumWidth += (visProtoCount - 1)*(g_StatusBarData.extraspace + 1);
		}

		if (g_StatusBarData.Align == 1) //center
			aligndx = (rectwidth - SumWidth) >> 1;
		else if (g_StatusBarData.Align == 2) //right
			aligndx = (rectwidth - SumWidth);

		// Draw in rects
		RECT r = rc;
		r.left += g_StatusBarData.rectBorders.left + aligndx;
		for (i = 0; i < visProtoCount; i++) {
			ProtoItemData& p = ProtosData[line*protosperline + i];
			HRGN rgn;
			HICON hIcon = NULL;
			HICON hxIcon = NULL;
			BOOL NeedDestroy = FALSE;
			int x = r.left;
			x += p.PaddingLeft;
			r.right = r.left + ProtoWidth[i];

			if (p.bShowProtoIcon) {
				if (p.iProtoStatus > ID_STATUS_OFFLINE && (p.xStatusMode & 3) > 0) {
					if (ProtoServiceExists(p.szAccountName, PS_GETCUSTOMSTATUSICON)) {
						hxIcon = p.extraIcon;
						if (hxIcon) {
							if ((p.xStatusMode & 3) == 2) {
								hIcon = GetMainStatusOverlay(p.iProtoStatus);
								NeedDestroy = TRUE;
							}
							else if ((p.xStatusMode & 3) == 1) {
								hIcon = hxIcon;
								NeedDestroy = TRUE;
								hxIcon = NULL;
							}
						}
					}
				}

				if (hIcon == NULL && (hxIcon == NULL || ((p.xStatusMode & 3) == 3))) {
					if ((p.bConnectingIcon == 1) && p.iProtoStatus >= ID_STATUS_CONNECTING && p.iProtoStatus <= ID_STATUS_CONNECTING + MAX_CONNECT_RETRIES) {
						hIcon = (HICON)CLUI_GetConnectingIconService((WPARAM)p.szAccountName, 0);
						if (hIcon)
							NeedDestroy = TRUE;
						else
							hIcon = LoadSkinnedProtoIcon(p.szAccountName, p.iProtoStatus);
					}
					else hIcon = LoadSkinnedProtoIcon(p.szAccountName, p.iProtoStatus);
				}

				rgn = CreateRectRgn(r.left, r.top, r.right, r.bottom);

				if (g_StatusBarData.sameWidth) {
					int fw = p.fullWidth;
					int rw = r.right - r.left;
					if (g_StatusBarData.Align == 1)
						x = r.left + ((rw - fw) / 2);
					else if (g_StatusBarData.Align == 2)
						x = r.left + ((rw - fw));
					else
						x = r.left;
				}

				SelectClipRgn(hDC, rgn);
				p.bDoubleIcons = false;

				DWORD dim = p.bIsDimmed ? ((64 << 24) | 0x80) : 0;

				if ((p.xStatusMode & 3) == 3) {
					if (hIcon)
						mod_DrawIconEx_helper(hDC, x, iconY, hIcon, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, NULL, DI_NORMAL | dim);
					if (hxIcon) {
						mod_DrawIconEx_helper(hDC, x + GetSystemMetrics(SM_CXSMICON) + 1, iconY, hxIcon, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, NULL, DI_NORMAL | dim);
						x += GetSystemMetrics(SM_CXSMICON) + 1;
					}
					p.bDoubleIcons = hIcon && hxIcon;
				}
				else {
					if (hxIcon)
						mod_DrawIconEx_helper(hDC, x, iconY, hxIcon, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, NULL, DI_NORMAL | dim);
					if (hIcon)
						mod_DrawIconEx_helper(hDC, x, iconY, hIcon, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, NULL, DI_NORMAL | ((hxIcon && (p.xStatusMode & 4)) ? (192 << 24) : 0) | dim);
				}

				if (hxIcon || hIcon) { /* TODO g_StatusBarData.bDrawLockOverlay  options to draw locked proto*/
					if (db_get_b(NULL, p.szAccountName, "LockMainStatus", 0)) {
						HICON hLockOverlay = LoadSkinnedIcon(SKINICON_OTHER_STATUS_LOCKED);
						if (hLockOverlay != NULL) {
							mod_DrawIconEx_helper(hDC, x, iconY, hLockOverlay, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, NULL, DI_NORMAL | dim);
							Skin_ReleaseIcon(hLockOverlay);
						}
					}
				}
				if (hxIcon) DestroyIcon_protect(hxIcon);
				if (NeedDestroy) DestroyIcon_protect(hIcon);
				else Skin_ReleaseIcon(hIcon);
				x += GetSystemMetrics(SM_CXSMICON) + 1;
			}

			if (p.bShowProtoName) {
				SIZE textSize;
				RECT rt = r;
				rt.left = x + (spaceWidth >> 1);
				rt.top = textY;
				ske_DrawText(hDC, p.tszProtoHumanName, lstrlen(p.tszProtoHumanName), &rt, 0);

				if ((p.bShowProtoEmails && p.szProtoEMailCount != NULL) || p.bShowStatusName || ((p.xStatusMode & 8) && p.tszProtoXStatus)) {
					GetTextExtentPoint32(hDC, p.tszProtoHumanName, lstrlen(p.tszProtoHumanName), &textSize);
					x += textSize.cx + 3;
				}
			}

			if (p.bShowProtoEmails && p.szProtoEMailCount != NULL) {
				SIZE textSize;
				RECT rt = r;
				rt.left = x + (spaceWidth >> 1);
				rt.top = textY;
				ske_DrawTextA(hDC, p.szProtoEMailCount, lstrlenA(p.szProtoEMailCount), &rt, 0);
				if (p.bShowStatusName || ((p.xStatusMode & 8) && p.tszProtoXStatus)) {
					GetTextExtentPoint32A(hDC, p.szProtoEMailCount, lstrlenA(p.szProtoEMailCount), &textSize);
					x += textSize.cx + 3;
				}
			}