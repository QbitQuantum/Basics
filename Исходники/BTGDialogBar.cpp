void CBTGVDialogBar::OnUpdate(void)
{
	CSliderCtrl *sRed, *sGreen, *sBlue, *sAlpha, *sBrightness;
	CButton *pButton;
	CEdit *eRed, *eGreen, *eBlue, *eAlpha, *eBrightness;
	char buffer[20];
	CString tRed, tGreen, tBlue, tAlpha, tBrightness;

	sRed = (CSliderCtrl *)GetDlgItem(ID_REDSLIDER);
	sGreen = (CSliderCtrl *)GetDlgItem(ID_GREENSLIDER);
	sBlue = (CSliderCtrl *)GetDlgItem(ID_BLUESLIDER);
	sAlpha = (CSliderCtrl *)GetDlgItem(ID_ALPHASLIDER);
	sBrightness = (CSliderCtrl *)GetDlgItem(ID_BRIGHTNESSSLIDER);
	pButton = (CButton *)GetDlgItem(IDC_COLORPREVIEW);

	eRed = (CEdit *)GetDlgItem(IDC_EDIT1);
	eGreen = (CEdit *)GetDlgItem(IDC_EDIT2);
	eBlue = (CEdit *)GetDlgItem(IDC_EDIT3);
	eAlpha = (CEdit *)GetDlgItem(IDC_EDIT4);
	eBrightness = (CEdit *)GetDlgItem(IDC_EDIT5);

	eRed->GetWindowText(tRed);
	eGreen->GetWindowText(tGreen);
	eBlue->GetWindowText(tBlue);
	eAlpha->GetWindowText(tAlpha);
	eBrightness->GetWindowText(tBrightness);

	// Has the slider changed?
	if((atoi(tRed) == red) && (sRed->GetPos() != red))
	{
		red = sRed->GetPos();
		bUpdate = 1;

		eRed->SetWindowText(itoa(sRed->GetPos(), buffer, 10));
	}

	// Has the edit changed?
	else if((atoi(tRed) != red) && (sRed->GetPos() == red))
	{
		red = atoi(tRed);
		if (red > 255) red = 255;

		bUpdate = 1;

		sRed->SetPos(red);
	}

	// Has the slider changed?
	if((atoi(tGreen) == green) && (sGreen->GetPos() != green))
	{
		green = sGreen->GetPos();
		bUpdate = 1;

		eGreen->SetWindowText(itoa(sGreen->GetPos(), buffer, 10));
	}

	// Has the edit changed?
	else if((atoi(tGreen) != green) && (sGreen->GetPos() == green))
	{
		green = atoi(tGreen);
		if (green > 255) green = 255;
		bUpdate = 1;

		sGreen->SetPos(green);
	}

	// Has the slider changed?
	if((atoi(tBlue) == blue) && (sBlue->GetPos() != blue))
	{
		blue = sBlue->GetPos();
		if (blue > 255) blue = 255;
		bUpdate = 1;

		eBlue->SetWindowText(itoa(sBlue->GetPos(), buffer, 10));
	}

	// Has the edit changed?
	else if((atoi(tBlue) != blue) && (sBlue->GetPos() == blue))
	{
		blue = atoi(tBlue);
		bUpdate = 1;

		sBlue->SetPos(blue);
	}

	// Has the slider changed?
	if((atoi(tAlpha) == alpha) && (sAlpha->GetPos() != alpha))
	{
		alpha = sAlpha->GetPos();
		if (alpha > 255) alpha = 255;
		bUpdate = 1;

		eAlpha->SetWindowText(itoa(sAlpha->GetPos(), buffer, 10));
	}

	// Has the edit changed?
	else if((atoi(tAlpha) != alpha) && (sAlpha->GetPos() == alpha))
	{
		alpha = atoi(tAlpha);
		bUpdate = 1;

		sAlpha->SetPos(alpha);
	}

	// Has the slider changed?
	if((atoi(tBrightness) == brightness) && (sBrightness->GetPos() != brightness))
	{
		brightness = sBrightness->GetPos();
		if (brightness > 255) brightness = 255;
		bUpdate = 1;

		eBrightness->SetWindowText(itoa(sBrightness->GetPos(), buffer, 10));
	}

	// Has the edit changed?
	else if((atoi(tBrightness) != brightness) && (sBrightness->GetPos() == brightness))
	{
		brightness = atoi(tBrightness);
		bUpdate = 1;

		sBrightness->SetPos(brightness);
	}

	if(bFloating != IsFloating())
	{
		bUpdate = 1;
		bFloating = IsFloating();
	}
	
	if(bUpdate)
	{
		CDC *pDC = pButton->GetDC();
		CRect tempRect;
		pButton->GetClientRect(&tempRect);
		CBrush tempBrush(RGB(red, green, blue));
		pDC->SelectObject(&tempBrush);
		pDC->Rectangle(tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);

		bUpdate = 0;
	}
}