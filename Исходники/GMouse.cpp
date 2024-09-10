void	GMouse::HideCursor(void)
{
#if defined(GWIN)
	HCURSOR hcurseur = LoadCursor(GetModuleHandle(NULL),"IDC_CURSOR");
	HCURSOR hcopiecurseur = CopyCursor(hcurseur);
	SetSystemCursor(hcopiecurseur, OCR_APPSTARTING);
	hcopiecurseur = CopyCursor(hcurseur);
	SetSystemCursor(hcopiecurseur, OCR_NORMAL);
#endif
}