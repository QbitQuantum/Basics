void CTreeOptionsCtrlEx::OnCreateImageList()
{
	CDC* pDCScreen = CDC::FromHandle(::GetDC(HWND_DESKTOP)); // explicitly use screen-dc, for proper RTL support
	if (pDCScreen)
	{
		const int iBmpWidth = 16;
		const int iBmpHeight = 16;
		const int iBitmaps = 13;
		CBitmap bmpControls;
		if (bmpControls.CreateCompatibleBitmap(pDCScreen, iBmpWidth*iBitmaps, iBmpHeight))
		{
			if (m_ilTree.Create(iBmpWidth, iBmpHeight, m_uImageListColorFlags | ILC_MASK, 0, 1))
			{
				CDC dcMem;
				if (dcMem.CreateCompatibleDC(pDCScreen))
				{
					HTHEME hTheme = (g_xpStyle.IsThemeActive() && g_xpStyle.IsAppThemed()) ? g_xpStyle.OpenThemeData(NULL, L"BUTTON") : NULL;
					CBitmap* pOldBmp = dcMem.SelectObject(&bmpControls);
					dcMem.FillSolidRect(0, 0, iBmpWidth*iBitmaps, iBmpHeight, GetSysColor(COLOR_WINDOW));

					//int iCtrlWidth = iBmpWidth - 2;
					//int iCtrlHeight = iBmpHeight - 2;
					int iCtrlWidth = 16 - 3;
					int iCtrlHeight = 16 - 3;
					int iCtrlLeft = (iBmpWidth - iCtrlWidth) / 2;
					int iCtrlTop = (iBmpHeight - iCtrlHeight) / 2;

					// checkbox
					CRect rcBmp(0, 0, 0+iBmpWidth, 0+iBmpHeight);
					CRect rcCtrl(iCtrlLeft, iCtrlTop, iCtrlLeft+iCtrlWidth, iCtrlTop+iCtrlHeight);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_CHECKBOX, CBS_UNCHECKEDNORMAL, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, CBS_UNCHECKEDNORMAL, &rcCtrl, 0, 0, NULL);
					}
					else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_FLAT);

					// checkbox checked
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*1);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_CHECKBOX, CBS_CHECKEDNORMAL, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, CBS_CHECKEDNORMAL, &rcCtrl, 0, 0, NULL);
					}
					else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_CHECKED | DFCS_FLAT);

					// radio
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*2);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_RADIOBUTTON, RBS_UNCHECKEDNORMAL, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, RBS_UNCHECKEDNORMAL, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONRADIO | DFCS_FLAT);

					// radio checked
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*3);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_RADIOBUTTON, RBS_CHECKEDNORMAL, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, RBS_CHECKEDNORMAL, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONRADIO | DFCS_CHECKED | DFCS_FLAT);

					// checkbox disabled
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*4);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_CHECKBOX, CBS_UNCHECKEDDISABLED, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, CBS_UNCHECKEDDISABLED, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_INACTIVE | DFCS_FLAT);

					// checkbox checked disabled
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*5);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_CHECKBOX, CBS_CHECKEDDISABLED, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, CBS_CHECKEDDISABLED, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONCHECK | DFCS_CHECKED | DFCS_INACTIVE | DFCS_FLAT);

					// radio disabled
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*6);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_RADIOBUTTON, RBS_UNCHECKEDDISABLED, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, RBS_UNCHECKEDDISABLED, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONRADIO | DFCS_INACTIVE | DFCS_FLAT);

					// radio checked disabled
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*7);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_RADIOBUTTON, RBS_CHECKEDDISABLED, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, RBS_CHECKEDDISABLED, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTONRADIO | DFCS_CHECKED | DFCS_INACTIVE | DFCS_FLAT);

					// checkbox checked tri-state
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*8);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_CHECKBOX, CBS_MIXEDNORMAL, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, CBS_MIXEDNORMAL, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTON3STATE | DFCS_CHECKED | DFCS_FLAT);

					// checkbox checked tri-state disabled 
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*9);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, BP_CHECKBOX, CBS_MIXEDDISABLED, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, BP_CHECKBOX, CBS_MIXEDDISABLED, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_BUTTON, DFCS_BUTTON3STATE | DFCS_CHECKED | DFCS_INACTIVE | DFCS_FLAT);

					ASSERT( TREEOPTSCTRLIMG_EDIT == 11 );
					rcBmp.MoveToX(iBmpWidth*11);
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*11);
					CFont font;
					if (font.CreatePointFont(10, _T("Courier")))
					{
						CFont* pOldFont = dcMem.SelectObject(&font);
						dcMem.TextOut(rcCtrl.left+2, rcCtrl.top, _T("I"));
						dcMem.SelectObject(pOldFont);
					}
					CRect rcEdge(rcBmp);
					rcEdge.top += 1;
					rcEdge.bottom -= 1;
					dcMem.DrawEdge(&rcEdge, EDGE_ETCHED, BF_RECT);

					if (hTheme){
						g_xpStyle.CloseThemeData(hTheme);
						hTheme = NULL;
					}

					hTheme = (g_xpStyle.IsThemeActive() && g_xpStyle.IsAppThemed()) ? g_xpStyle.OpenThemeData(NULL, L"COMBOBOX") : NULL;
					rcCtrl.MoveToX(iCtrlLeft+iBmpWidth*12);
					if (hTheme){
						g_xpStyle.DrawThemeBackground(hTheme, dcMem, CP_DROPDOWNBUTTON, CBXS_NORMAL, &rcCtrl, NULL);
						g_xpStyle.DrawThemeEdge(hTheme, dcMem, CP_DROPDOWNBUTTON, CBXS_NORMAL, &rcCtrl, 0, 0, NULL);
					} else
						dcMem.DrawFrameControl(&rcCtrl, DFC_SCROLL, DFCS_SCROLLCOMBOBOX | DFCS_FLAT);

					dcMem.SelectObject(pOldBmp);
					m_ilTree.Add(&bmpControls, RGB(255,0,255));
					if (hTheme)
						g_xpStyle.CloseThemeData(hTheme);
				}
			}
		}
		::ReleaseDC(HWND_DESKTOP, *pDCScreen);
	}
}