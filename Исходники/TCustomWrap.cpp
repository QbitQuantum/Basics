void CCustomWrapAppControl::ConstructL()
	{
	CreateWindowL();
    Window().SetShadowDisabled(ETrue);
	CreateEdwinL();
	iStandardCustomWrap = iEdwin->TextLayout()->CustomWrap();
	iFocusControl=iEdwin;
	SetExtentToWholeScreen();
	ActivateL();
	iFocusControl->SetFocus(ETrue);
	}