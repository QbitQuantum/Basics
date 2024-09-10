void D9Draw::DrawTextW(const wchar_t* text, unsigned long font, util::Color color, util::Vector2 pos) {
	RECT tpos;
	tpos.left = (long)pos.x;
	tpos.top = (long)pos.y;

	ID3DXFont* nativeFont = reinterpret_cast<ID3DXFont*>(font);
	nativeFont->DrawTextW(0, text, wcslen(text), &tpos, DT_NOCLIP, color.GetD3DColor());
}