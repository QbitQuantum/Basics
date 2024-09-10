bool DXAPI::InitFont(){
	int fontsize = 500;
	LOGFONT lf = {fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
	CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN,"ＭＳ 明朝"};
	HFONT hFont;
	if(!(hFont = CreateFontIndirect(&lf))){
		return false;
	}
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// 文字コード取得
	TCHAR *c = "あ";
	UINT code = 0;
	if(IsDBCSLeadByte(*c))
		code = (BYTE)c[0]<<8 | (BYTE)c[1];
	else
		code = c[0];

	/*
	// フォントビットマップ取得
	GetTextMetrics( hdc, &TM );
	CONST MAT2 Mat = {{0,1},{0,0},{0,0},{0,1}};
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);
	*/

	// デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	ReleaseDC(NULL, hdc);

	return true;
}