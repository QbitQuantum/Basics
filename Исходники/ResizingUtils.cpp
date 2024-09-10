extern void
CResizerInit(CResizer *cs, HINSTANCE hInst, HWND dlg, int iIDD)
{
	BOOL bDialogEx = 0;

	/* set variables */
	cs->inst = hInst;
	cs->IDD  = iIDD;
	cs->hwnd = dlg;

	/* Get current point size information */
	HDC hdcScreen = GetDC(NULL);

	if (!hdcScreen) {
		cs->dpi = 96;
	}
	else {
		cs->dpi = GetDeviceCaps(hdcScreen, LOGPIXELSX);
		ReleaseDC(NULL, hdcScreen);
	}

	helper::DLGTEMPLATEEX *lpDialogTemplate;

	if (!hInst)
		{ } // hInst = AfxFindResourceHandle(IMAKEINTRESOURCE(IDD), RT_DIALOG);

	HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(cs->IDD), RT_DIALOG);
	HANDLE hDialogTemplate = LoadResource(hInst, hResource);
	lpDialogTemplate = (helper::DLGTEMPLATEEX *)LockResource(hDialogTemplate);

	bDialogEx = helper::IsDialogEx((const DLGTEMPLATE*) lpDialogTemplate);

	querydialogdata((LPCSTR)lpDialogTemplate, &cs->sDialogData);
/*	cs->sDialogData.style	= lpDialogTemplate->style;
	cs->sDialogData.exStyle	= lpDialogTemplate->exStyle;
 */
	if ((cs->sDialogData.pt<0)||(cs->sDialogData.pt>32767))
	{
		// I don't know what to do if it happens this way
		// this is a compromise solution:
		cs->sDialogData.pt = -cs->sDialogData.pt;
		cs->sDialogData.pt &= 0xFFFF;
	}

	cs->font=CreateFontW(
		-(int)(cs->sDialogData.pt*96.0/72.0 + 0.5), // negative makes it use "char size"
	0,              // logical average character width
	0,              // angle of escapement
	0,              // base-line orientation angle
	cs->sDialogData.weight,  // weight
	cs->sDialogData.italic,  // italic
	FALSE,          // underline attribute flag
	FALSE,          // strikeout attribute flag
	DEFAULT_CHARSET,    // character set identifier
	OUT_DEFAULT_PRECIS, // output precision
	CLIP_DEFAULT_PRECIS,// clipping precision
	DEFAULT_QUALITY,    // output quality
	DEFAULT_PITCH,  // pitch and family
	cs->sDialogData.faceName  // pointer to typeface name string
	);

	cs->oldfont=(HFONT)::SendMessage(cs->hwnd, WM_GETFONT, 0, 0);
	SendMessage(cs->hwnd, WM_SETFONT, (LPARAM)cs->font, TRUE);

	/* Pick up all of the item ID's */
	/* go through the Item ID's to resize them */
	helper::DLGITEMTEMPLATEEX *itemE =
		(helper::DLGITEMTEMPLATEEX *)helper::FindFirstDlgItem((DLGTEMPLATE *)lpDialogTemplate);
	DLGITEMTEMPLATE *item = (DLGITEMTEMPLATE *) itemE;

	cs->jNtItems = 0;
	int jMax = helper::DlgTemplateItemCount((DLGTEMPLATE *)lpDialogTemplate);
	while (cs->jNtItems < jMax) {
		if (bDialogEx) {
			cs->asDI[cs->jNtItems].x = itemE->x;
			cs->asDI[cs->jNtItems].y = itemE->y;
			cs->asDI[cs->jNtItems].cx= itemE->cx;
			cs->asDI[cs->jNtItems].cy= itemE->cy;
			cs->asDI[cs->jNtItems].id= itemE->id;
			itemE=(helper::DLGITEMTEMPLATEEX *)helper::FindNextDlgItem((DLGITEMTEMPLATE *)itemE,TRUE);
		}
		else {
			cs->asDI[cs->jNtItems].x = item->x;
			cs->asDI[cs->jNtItems].y = item->y;
			cs->asDI[cs->jNtItems].cx= item->cx;
			cs->asDI[cs->jNtItems].cy= item->cy;
			cs->asDI[cs->jNtItems].id= item->id;
			cs->asDI[cs->jNtItems].uiFlags = 0;
			item = helper::FindNextDlgItem(item,FALSE);
		}
		cs->asDI[cs->jNtItems].uiFlags = 0;
		cs->jNtItems++;
	}

	UnlockResource(hDialogTemplate);
	FreeResource(hDialogTemplate);

	cs->x_factor = (double) 2;
	cs->y_factor = (double) 2;

}	/* CResizerInit */