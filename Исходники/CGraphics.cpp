float CGraphics::GetCharacterWidth(char c, float fScale)
{
	// Get the font
	LPD3DXFONT pFont = GetFont(0);

	// Is the font valid?
	if(pFont)
	{
		HDC dc = pFont->GetDC();
		SIZE size;
		GetTextExtentPoint32(dc, &c, 1, &size);
		return ((float)size.cx * fScale);
	}

	return 0.0f;
}