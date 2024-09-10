LRESULT CSetPgAppear::OnInitDialog(HWND hDlg, bool abInitial)
{
	checkDlgButton(hDlg, cbHideCaption, gpSet->isHideCaption);

	checkDlgButton(hDlg, cbHideCaptionAlways, gpSet->isHideCaptionAlways());
	EnableWindow(GetDlgItem(hDlg, cbHideCaptionAlways), !gpSet->isForcedHideCaptionAlways());

	// Скрытие рамки
	SetDlgItemInt(hDlg, tHideCaptionAlwaysFrame, gpSet->HideCaptionAlwaysFrame(), TRUE);
	SetDlgItemInt(hDlg, tHideCaptionAlwaysDelay, gpSet->nHideCaptionAlwaysDelay, FALSE);
	SetDlgItemInt(hDlg, tHideCaptionAlwaysDissapear, gpSet->nHideCaptionAlwaysDisappear, FALSE);

	checkDlgButton(hDlg, cbEnhanceGraphics, gpSet->isEnhanceGraphics);

	//checkDlgButton(hDlg, cbEnhanceButtons, gpSet->isEnhanceButtons);

	//checkDlgButton(hDlg, cbAlwaysShowScrollbar, gpSet->isAlwaysShowScrollbar);
	checkRadioButton(hDlg, rbScrollbarHide, rbScrollbarAuto, (gpSet->isAlwaysShowScrollbar==0) ? rbScrollbarHide : (gpSet->isAlwaysShowScrollbar==1) ? rbScrollbarShow : rbScrollbarAuto);
	SetDlgItemInt(hDlg, tScrollAppearDelay, gpSet->nScrollBarAppearDelay, FALSE);
	SetDlgItemInt(hDlg, tScrollDisappearDelay, gpSet->nScrollBarDisappearDelay, FALSE);

	checkDlgButton(hDlg, cbAlwaysOnTop, gpSet->isAlwaysOnTop);

	#ifdef _DEBUG
	checkDlgButton(hDlg, cbTabsInCaption, gpSet->isTabsInCaption);
	#else
	ShowWindow(GetDlgItem(hDlg, cbTabsInCaption), SW_HIDE);
	#endif

	checkDlgButton(hDlg, cbNumberInCaption, gpSet->isNumberInCaption);

	checkDlgButton(hDlg, cbMultiCon, gpSet->mb_isMulti);
	checkDlgButton(hDlg, cbMultiShowButtons, gpSet->isMultiShowButtons);
	checkDlgButton(hDlg, cbMultiShowSearch, gpSet->isMultiShowSearch);

	checkDlgButton(hDlg, cbSingleInstance, gpSetCls->IsSingleInstanceArg());
	enableDlgItem(hDlg, cbSingleInstance, (gpSet->isQuakeStyle == 0));

	checkDlgButton(hDlg, cbShowHelpTooltips, gpSet->isShowHelpTooltips);

	return 0;
}