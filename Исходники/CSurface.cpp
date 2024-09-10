void CSurface::Init(char* filename)
{
	Gdiplus::GdiplusStartupInput startupInput;
	ULONG_PTR token;
	GdiplusStartup(&token, &startupInput, NULL);

	int len = strlen(filename);
	wchar_t* temp = new wchar_t[len + 1];
	for (int i = 0; i < len; i++)
	{
		temp[i] = filename[i];
	}
	temp[len] = '\0';
	Gdiplus::Bitmap bitmap(temp);
	Gdiplus::Color pixel;

	if (bitmap.GetWidth() <= 0)
		return;
	if (bitmap.GetHeight() <= 0)
		return;

	m_width = bitmap.GetWidth();
	m_height = bitmap.GetHeight();

	m_pPixels = new CVector4[m_width * m_height];

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			bitmap.GetPixel(x, y, &pixel);
			m_pPixels[x + y * m_width] = CVector4(pixel.GetR(), pixel.GetG(), pixel.GetB(), pixel.GetA());
		}
	}

	if (!m_pPixels)
		return;

	STRING::Copy(m_pFilename, filename);
}