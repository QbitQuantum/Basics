BOOL Set_ImgRes(INT nIdx)
{
	TCHAR waMenuItemStr[BUF_LENGTH];
	TCHAR waWidth[BUF_LENGTH], waHeight[BUF_LENGTH];
	TCHAR* pwChar;
	ImageRes tIRes;

	g_ResIdx = nIdx;	// Store the current resolution point globally
	g_hmnuCurr = (HMENU) SendMessage(g_hwndMenuBar, SHCMBM_GETSUBMENU, 0, IDM_SETTINGS);
	RemoveMenu(g_hmnuCurr, 12, MF_BYPOSITION);

	if(g_bVideoMode)
	{
		AppendMenu(g_hmnuCurr, MF_STRING | MF_POPUP, (UINT)g_ahmnuVdoColorFmts[nIdx], L"&ColorFmts");	
		
		g_hmnuCurr = g_ahmnuVdoColorFmts[nIdx];
		CheckMenuRadioItem(g_hmnuCurr, 0, (g_nNoOfVdoCap-1), 0, MF_BYPOSITION);
		GetMenuString(g_hmnuCurr, 0, waMenuItemStr, BUF_LENGTH, MF_BYPOSITION);
		g_wsColorFmt = waMenuItemStr;

		g_hmnuCurr = g_hmnuVideoSub;
		CheckMenuRadioItem(g_hmnuCurr, 0, (g_nNoOfVdoCap-1), nIdx, MF_BYPOSITION);
	}
	else
	{
		AppendMenu(g_hmnuCurr, MF_STRING | MF_POPUP, (UINT)g_ahmnuStillColorFmts[nIdx], L"&ColorFmts");	

		g_hmnuCurr = g_ahmnuStillColorFmts[nIdx];
		CheckMenuRadioItem(g_hmnuCurr, 0, (g_nNoOfStillCap-1), 0, MF_BYPOSITION);
		GetMenuString(g_hmnuCurr, 0, waMenuItemStr, BUF_LENGTH, MF_BYPOSITION);
		g_wsColorFmt = waMenuItemStr;

		g_hmnuCurr = g_hmnuStillSub;
		CheckMenuRadioItem(g_hmnuCurr, 0, (g_nNoOfStillCap-1), nIdx, MF_BYPOSITION);
	}

	GetMenuString(g_hmnuCurr, nIdx, waMenuItemStr, BUF_LENGTH, MF_BYPOSITION);
	OutputDebugString(waMenuItemStr);
	pwChar = wcsstr(waMenuItemStr, L"X");
	wcscpy(waHeight, (pwChar+2));
	wmemcpy(waWidth, waMenuItemStr, ((pwChar-1)-waMenuItemStr));
	waWidth[(pwChar-1)-waMenuItemStr]='\0';

#ifdef DEBUG_MODE
	OutputDebugString(L"\n---------------------\n");
	OutputDebugString(waMenuItemStr);
	OutputDebugString(L"\n|");
	OutputDebugString(waWidth);
	OutputDebugString(L"|");
	OutputDebugString(L"\n|");
	OutputDebugString(waHeight);
	OutputDebugString(L"|\n---------------------");
#endif
	tIRes.nWidth = atoi(waWidth);
	tIRes.nHeight = _wtoi(waHeight);		//tIRes.nHeight = atoi(waHeight);

	if(!((tIRes.nWidth==g_tImgRes.nWidth)&&(tIRes.nHeight==g_tImgRes.nHeight)&&
		(g_bVMod==g_bVideoMode)))
	{
		//Record the selected resolution gloablly
		g_tImgRes.nWidth = tIRes.nWidth;
		g_tImgRes.nHeight = tIRes.nHeight;
		g_bVMod = g_bVideoMode;

		//wsprintf(test, L"\nWidth :- %d Height :- %d", tIRes.nWidth, tIRes.nHeight);
		//OutputDebugString(test);
		//g_Prop.Set_Resolution(&tIRes, P);
		/*
		ImageRes ptRes;
		ptRes.nHeight=240;
		ptRes.nWidth=320;
		g_Prop.Set_Resolution(&ptRes, P);
		*/
		if(g_bVideoMode)
			g_Prop.Set_Resolution(&tIRes, V);
		else
			g_Prop.Set_Resolution(&tIRes, S);

		OutputDebugString(L"\n-----------Resolution Change OK-----------");
	}
	else
	{
		OutputDebugString(L"\n-----------Same Resolution-----------");
	}
	
return TRUE;
}