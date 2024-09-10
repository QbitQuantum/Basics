void OPENGL_3D_ENGNIE::CreateCharaterShowList()
{
	//set the charater size and type
	HFONT hFont = CreateFontA(24, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Comic Sans MS");
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);

	CharShowList = glGenLists(128);
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, CharShowList);
}