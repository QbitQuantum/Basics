/// <summary>Draws some text to the screen at the specified coordinates
/// with the given color, drawing from the display parameters initialized
/// in this display manager's constructor.</summary>
/// <param name="pDevice">LPDIRECT3DDEVICE9 to render to.</param>
/// <param name="x">Screen X coordinate to draw to.</param>
/// <param name="y">Screen Y coordinate to draw to.</param>
/// <param name="alpha">Alpha level for the rectangle (transparency).</param>
/// <param name="r">Red color component for the colour of the rectangle.</param>
/// <param name="g">Green color component for the colour of the rectangle.</param>
/// <param name="b">Blue color component for the colour of the rectangle.</param>
/// <param name="message">String to draw.</param>
/// <param name="fontType">D3DDisplayManager::FontType value to describe the
/// type of font which should be used.</param>
bool D3DDisplayManager::DrawCooldownTextToScreen(LPDIRECT3DDEVICE9 pDevice,
		unsigned int x,	unsigned int y, int alpha, int r, int g, int b,
		LPCSTR message,	FontType fontType) {

	_CreateFont(pDevice);

	// Choose our font based on input
	LPD3DXFONT font;
	switch (fontType) {
		case FontType::TITLE:
			font = pTitleFont;
			break;
		default:
			font = pFont;
	}

	D3DCOLOR fontColor = D3DCOLOR_ARGB(alpha, r, g, b);
	RECT rct;
	rct.left = x;
	rct.right = x + ((mDisplayParams.backdropWidth / 5) * 4);
	rct.top = y;
	rct.bottom = rct.top + mDisplayParams.backdropHeight;

	// TODO: add better support for different resolutions:
	// Use a lookup table to adjust font size dynamically?

	// Draw the text
	pFontSprite->Begin(D3DXSPRITE_SORT_TEXTURE);
	font->DrawTextA(pFontSprite, message, -1, &rct, DT_RIGHT, fontColor);
	pFontSprite->End();
	return true;
}