void CAllToolSetupSheet::OnPaint() 
{
	WINDOWPLACEMENT wp;
	RECT rect;

	wp.length = sizeof(WINDOWPLACEMENT);  //not sure if this is still required, but what the hey 
	GetWindowPlacement(&wp);

	if (InitDialogComplete && wp.showCmd!=SW_SHOWMAXIMIZED && wp.showCmd!=SW_SHOWMINIMIZED)  // save the dialog window position
	{
        GetWindowRect(&rect);
		LastMoveX = rect.left;
		LastMoveY = rect.top;
		LastSizeX = rect.right - rect.left;
		LastSizeY = rect.bottom - rect.top;
	}
	CMySheet::OnPaint();
}