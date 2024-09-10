bool CGutFontUniCodeOpenGL::AccessTexture(WCHAR c, int &x, int &y)
{
	bool bUpdateTexture = CGutFontUniCode::AccessTexture(c, x, y);
	
	if ( bUpdateTexture )
	{
		float tX = (float)x / (float)m_iLayoutW;
		float tY = (float)y / (float)m_iLayoutH;
		float tW = 1.0f/(float)m_iLayoutW;
		float tH = 1.0f/(float)m_iLayoutH;
		
		int left = tX * m_iTextureW;
		int width = tW * m_iTextureW;
		int right = left + width;
		int top = tY * m_iTextureH;
		int height = tH * m_iTextureH;
		int bottom = top + height;

		unsigned char *pBuffer = new unsigned char[width*height];
		unsigned char *buffer = pBuffer;

		for ( int y=0; y<height; y++ )
		{
			for ( int x=0; x<width; x++ )
			{
				COLORREF rgb = GetPixel(m_MemDC, x, y);

				int grayscale = GetRValue(rgb) + GetGValue(rgb) + GetBValue(rgb);
				grayscale /= 3;

				*buffer++ = grayscale;
			}
		}

		glBindTexture(GL_TEXTURE_2D, m_FontTexture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, left, top, width, height, GL_ALPHA,  GL_UNSIGNED_BYTE, pBuffer);

		delete [] pBuffer;
	}

	return true;
}