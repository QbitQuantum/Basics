void	Dialog_RemoteConnProps::Draw()
{
	setcol(fontcolor, backcolor, GetWin());
	wmove(GetWin(), height-3, 2);
	whline(GetWin(), HLINE, width-4);

	CheckRadioButton*		pChkButton = NULL;

	for (int n = _nViewFirstCur; n < _nViewFirstCur+_nViewSize; n++)
	{
		if (n < (int)_vButtonList.size())
		{
			pChkButton = _vButtonList[n];
			pChkButton->SetForm((Form*)this);
			pChkButton->width = _nStrMaxLength;

			pChkButton->Move( 3 + n - _nViewFirstCur, 2 );
			pChkButton->backcolor = g_tColorCfg.GetColorEntry("PropertyList").back;
			pChkButton->fontcolor = g_tColorCfg.GetColorEntry("PropertyList").font;

			pChkButton->Show();

			if (_nCur == n)
				pChkButton->SetFocus(true);
			else
				pChkButton->SetFocus(false);
		}
	}

	Button*		pButton = NULL;

	for (int n = 0; n < (int)_vGenaralButton.size(); n++)
	{
		pButton = _vGenaralButton[n];
		pButton->SetForm((Form*)this);

		pButton->backcolor = g_tColorCfg.GetColorEntry("PropertyBtn").back;
		pButton->fontcolor = g_tColorCfg.GetColorEntry("PropertyBtn").font;

		if ( n < (int)_vGenaralButton.size() - 1 )
			pButton->Move(3+(n*2), width-12);
		else
			pButton->Move(height-2, width-12);
		pButton->SetTxtAlign(MIDDLE);
	
		pButton->Show();
		pButton->SetFocus(false);
		if (_nStatusNum == n + 1)
			pButton->SetFocus(true);
	}
}