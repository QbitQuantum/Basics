void FGAPIENTRY
glutTrueTypeStringPoints(WCHAR *fontname, int fontsize, int style, int x, int y, const WCHAR *string)
{
	int len, xx = 0, yy = 0, nbpoints = 0, i;
	GLshort *points;
	GLushort *indices;
	HFONT font;
	LOGFONTW	lf;	
	RECT rect;
	static HBITMAP bmp;
	static BYTE *img;
	static HDC hdc = NULL;
	static BITMAPINFO bi;
	SIZE sz;
	static EGLint width, height;

	if(!fontname || !string)
		return;
	if(!string[0])
		return;

	// Initialize static DC and DIB bitmap on the first call
	if(!hdc)
	{		
		// Create a device compatible DC
		hdc = CreateCompatibleDC(GetDC(fgStructure.Window->Window.Handle));	
		
		eglQuerySurface(fgDisplay.eglDisplay, fgStructure.Window->Window.Surface, EGL_WIDTH, &width);
		eglQuerySurface(fgDisplay.eglDisplay, fgStructure.Window->Window.Surface, EGL_HEIGHT, &height);

		// Create a DIB bitmap and attach it to the DC
		ZeroMemory(&bi, sizeof(BITMAPINFO));
		bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = width;
		bi.bmiHeader.biHeight = height; 
		bi.bmiHeader.biBitCount = 8;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biCompression = BI_RGB;
		
		bmp = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &img, NULL, 0);
	
		SelectObject(hdc, bmp);
		
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));			
	}

	// Erase DC content	with the current black brush
	//Rectangle(hdc, 0, 0, width, height);
	ZeroMemory(img, width * height);

	// Create the font handle and attach it to the DC
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfEscapement = 0;
	wcscpy(lf.lfFaceName, fontname);
	lf.lfHeight = -(fontsize * GetDeviceCaps(GetDC(fgStructure.Window->Window.Handle), LOGPIXELSY) / 72);
	lf.lfItalic = (style & 1) ? TRUE : FALSE;
	lf.lfOrientation = 0;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfStrikeOut = FALSE;
	lf.lfUnderline = (style & 4) ? TRUE : FALSE;
	lf.lfWidth = 0;
	lf.lfWeight = (style & 2) ? FW_BOLD : FW_NORMAL;
	
	font = CreateFontIndirectW(&lf);

	SelectObject(hdc, font);

	// Draw text in white onto the bitmap
	len = wcslen(string);

	GetTextExtentPointW(hdc, string, len, &sz);

	rect.left = max(0, min(x, width));
	rect.top = max(0, min(y, height));
	rect.right = min(rect.left + sz.cx, width);
	rect.bottom = min(rect.top + sz.cy, height);

	DrawTextW(hdc, string, len, &rect, DT_LEFT | DT_BOTTOM);
	
	// Traverse the bitmap and add all white pixels into a points buffer
	points = (GLshort*)malloc(sz.cx * sz.cy * 2 * sizeof(short));

	for(yy = rect.top; yy < rect.bottom; yy++)
	{
		for(xx = rect.left; xx < rect.right; xx++)
		{
			if(img[xx + (height - yy) * width] != 0)
			{
				points[nbpoints * 2 + 0] = xx - x;
				points[nbpoints * 2 + 1] = (short)(rect.top + sz.cy - (yy - rect.top)) - y;
				nbpoints++;
			}
		}
	}

	// Delete GDI font object
	DeleteObject(font);
	
	// Prepare the index buffer
	indices = (GLushort*)malloc(nbpoints * sizeof(GLushort));
	for(i = 0; i < nbpoints; i++)
		indices[i] = i;

	// Draw the points buffer
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity(); 

	glOrthox(0, _INT2FIXED(width), 
			0, _INT2FIXED(height), 
			0, _INT2FIXED(1));


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    glLoadIdentity(); 

	glDisable(GL_DEPTH_TEST);
	
	glTranslatex(_INT2FIXED(x), _INT2FIXED(y), 0);	
	
	glEnable(GL_ALPHA_TEST);
    glAlphaFuncx(GL_NOTEQUAL, 0);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
	glEnableClientState (GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_SHORT, 0, points);

	glDrawElements(GL_POINTS,
                        nbpoints,
                        GL_UNSIGNED_SHORT,
                        indices);
	
	glDisable(GL_ALPHA_TEST);

	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	free(indices);
	free(points);
}