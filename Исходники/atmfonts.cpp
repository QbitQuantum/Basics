void ATMFontMan::FindClosestFont()
{
	CDC Screen;
	if (Screen.CreateIC(TEXT("DISPLAY"), 0, 0, 0))
	{
		EnumFontFamilies(Screen.m_hDC,
						 NULL,
						 (FONTENUMPROC) ATMFontMan_CallBackFindClosestFont,
						 NULL);
		Screen.DeleteDC();
	}
}