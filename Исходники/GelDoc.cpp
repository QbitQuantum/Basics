void CGelDoc::OnGelHueRight() 
{
	CPalette* pPal = AfxGetPaletteApp()->GetAppPalette();
	if (!pPal)
		return;

	int i;
	for (i = 0; i < 256; i++)
	{
		if (m_abySelection[i])
		{
			PALETTEENTRY entry;
			BYTE k;
			pPal->GetPaletteEntries(i, 1, &entry);
			k = pPal->GetNearestPaletteIndex(
				RGB(entry.peBlue, entry.peRed, entry.peGreen));
			m_abyTransform[i] = k;
		}
	}

	SetModifiedFlag();
	ApplyGel();
}