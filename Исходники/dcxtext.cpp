void DcxText::DrawClientArea(HDC hdc)
{
	RECT r;
	// Setup alpha blend if any.
	LPALPHAINFO ai = this->SetupAlphaBlend(&hdc);

	TString wtext;
	TGetWindowText(this->m_Hwnd, wtext);

	GetClientRect(this->m_Hwnd, &r);

	DcxControl::DrawCtrlBackground(hdc,this,&r);

	HFONT oldFont = NULL;
	COLORREF oldClr = CLR_INVALID;
	COLORREF oldBkgClr = CLR_INVALID;

	// check if font is valid & set it.
	if (this->m_hFont != NULL)
		oldFont = SelectFont(hdc, this->m_hFont);
	// check if control is enabled.
	if (IsWindowEnabled(this->m_Hwnd)) {
		if (this->m_clrText != CLR_INVALID)
			oldClr = SetTextColor(hdc, this->m_clrText);
		if (this->m_clrBackText != CLR_INVALID)
			oldBkgClr = SetBkColor(hdc, this->m_clrBackText);
	}
	else { // disabled controls colouring
		oldClr = SetTextColor(hdc, GetSysColor(COLOR_GRAYTEXT));
		oldBkgClr = SetBkColor(hdc, GetSysColor(COLOR_3DFACE));
	}

	//UINT style = DT_LEFT;
	//if (this->isStyle(SS_CENTER))
	//	style = DT_CENTER;
	//if (this->isStyle(SS_RIGHT))
	//	style = DT_RIGHT;
	//if (this->isStyle(SS_ENDELLIPSIS))
	//	style |= DT_END_ELLIPSIS;
	//if (this->isStyle(SS_PATHELLIPSIS))
	//	style |= DT_PATH_ELLIPSIS;
	//if (this->isStyle(SS_NOPREFIX))
	//	style |= DT_NOPREFIX;
	//if (this->isStyle(SS_LEFTNOWORDWRAP))
	//	style |= DT_SINGLELINE;
	//else
	//	style |= DT_WORDBREAK; // changed for autowrap between words

	//this->ctrlDrawText(hdc, wtext, &r, style);

	this->ctrlDrawText(hdc, wtext, &r, this->m_uiStyle);

	if (oldBkgClr != CLR_INVALID)
		SetBkColor(hdc, oldBkgClr);
	if (oldClr != CLR_INVALID)
		SetTextColor(hdc, oldClr);
	if (oldFont != NULL)
		SelectFont(hdc, oldFont);

	this->FinishAlphaBlend(ai);
}