//handles actually creating the associated texture given the list of glyphs that have their positioning
//and dimension information filled out
static bool CreateGlyphTexture(CTextureStringGlyph* pGlyphs, uint32 nNumGlyphs, HDC hDC, 
							   uint8* pDibBits, const BITMAPINFO& bmi, const TEXTMETRICW& textMetric,
							   HTEXTURE & hTexture)
{
	//run through and build up the maximum extents from the glyph black boxes
	uint32 nMaxWidth = 0;
	uint32 nMaxHeight = 0;

	for(uint32 nCurrGlyph = 0; nCurrGlyph < nNumGlyphs; nCurrGlyph++)
	{
		nMaxWidth = LTMAX(nMaxWidth, pGlyphs[nCurrGlyph].m_rBlackBox.GetWidth());
		nMaxHeight = LTMAX(nMaxHeight, pGlyphs[nCurrGlyph].m_rBlackBox.GetHeight());
	}

	//the spacing added to each glyph dimension
	const uint32 knCharSpacing = 2;

	//determine the size of this texture that we will need
	SIZE sizeTexture;
	if(!GetTextureSizeFromCharSizes(pGlyphs, nNumGlyphs, nMaxWidth, nMaxHeight, knCharSpacing, sizeTexture ))
	{
		//the font is to big to fit into a texture, we must fail
		return false;
	}



	// This will be filled in with the pixel data of the font.
	uint8* pImageData = NULL;

	//lock down our texture for writing
//	uint32 nWidth, nHeight, 
	uint32 nPitch;
//	uint8* pImageData;

	// Calculate the pixeldata pitch.
	nPitch = WIDTHBYTES( 16, sizeTexture.cx );
	int nPixelDataSize = nPitch * sizeTexture.cy;


	// Allocate an array to copy the font into.
	LT_MEM_TRACK_ALLOC( pImageData = new uint8[ nPixelDataSize ],LT_MEM_TYPE_UI );
	if ( pImageData == NULL )
	{
		DEBUG_PRINT( 1, ("CreateGlyphTexture:  Failed to allocate pixeldata." ));
		return false;
	}


	// set the whole font texture to pure white, with alpha of 0.  When
	// we copy the glyph from the bitmap to the pixeldata, we just
	// affect the alpha, which allows the font to antialias with any color.
	uint16* pData = (uint16*)pImageData;
	uint16* pPixelDataEnd = (uint16*)(pImageData + nPixelDataSize);
	while( pData < pPixelDataEnd )
	{
		pData[0] = 0x0FFF;
		pData++;
	}

	// This will hold the UV offset for the font texture.
	POINT sizeOffset;
	sizeOffset.x = 0;
	sizeOffset.y = 0;

	//success flag
	bool bSuccess = true;

	// Iterate over the characters.
	for( uint32 nGlyph = 0; nGlyph < nNumGlyphs; nGlyph++ )
	{
		// Clear the bitmap out for this glyph if it's not the first.  The first glyph
		// gets a brand new bitmap to write on.
		if( nGlyph != 0 )
		{
			memset( pDibBits, 0, bmi.bmiHeader.biSizeImage );
		}

		//cache the glyph we will be operating on
		CTextureStringGlyph& Glyph = pGlyphs[nGlyph];

		// Get this character's width.
		wchar_t cChar = Glyph.m_cGlyph;
		int nCharWidthWithSpacing = Glyph.m_rBlackBox.GetWidth() + knCharSpacing;

		// See if this width fits in the current row.
		int nCharRightSide = sizeOffset.x + nCharWidthWithSpacing;
		if( nCharRightSide >= sizeTexture.cx )
		{
			// Doesn't fit in the current row.  Go to the next row.
			sizeOffset.x = 0;
			sizeOffset.y += nMaxHeight + knCharSpacing;
		}

		// Write the glyph out so that the smallest box around the glyph starts
		// at the bitmap's 0,0.
		POINT ptTextOutOffset;
		ptTextOutOffset.x = -Glyph.m_rBlackBox.Left();
		ptTextOutOffset.y = -Glyph.m_rBlackBox.Top();

		// Write out the glyph.  We can't use GetGlyphOutline to get the bitmap since
		// it has a lot of corruption bugs with it.  

		if( !TextOutW( hDC, ptTextOutOffset.x, ptTextOutOffset.y, &cChar, 1 ))
		{
			bSuccess = false;
			break;
		}

		// Make sure the GDI is done with our bitmap.
		GdiFlush( );

		LTRect2n rCopyTo;
		rCopyTo.Left()		= sizeOffset.x + (knCharSpacing / 2);
		rCopyTo.Top()		= sizeOffset.y + (knCharSpacing / 2);
		rCopyTo.Right()		= rCopyTo.Left() + Glyph.m_rBlackBox.GetWidth();
		rCopyTo.Bottom()	= rCopyTo.Top() + Glyph.m_rBlackBox.GetHeight();

		// Find pointer to region within the pixel data to copy the glyph
		// and copy the glyph into the pixeldata.
		CopyGlyphBitmapToPixelData( bmi, pDibBits, rCopyTo, textMetric, pImageData, sizeTexture );

		//setup the UV coordinates for this glyph
		Glyph.m_fU = (float)(rCopyTo.Left() + 0.5f) / (float)sizeTexture.cx;
		Glyph.m_fV = (float)(rCopyTo.Top() + 0.5f) / (float)sizeTexture.cy;
		Glyph.m_fTexWidth  = rCopyTo.GetWidth() / (float)sizeTexture.cx;
		Glyph.m_fTexHeight = rCopyTo.GetHeight() / (float)sizeTexture.cy;

		// Update to the next offset for the next character.
		sizeOffset.x += nCharWidthWithSpacing;
	}


	//if we succeeded in rendering all the characters, convert it to a texture
	if(bSuccess)
	{

		// turn pixeldata into a texture
		g_pILTTextureMgr->CreateTextureFromData(
				hTexture, 
				TEXTURETYPE_ARGB4444,
				TEXTUREFLAG_PREFER16BIT | TEXTUREFLAG_PREFER4444,
				pImageData, 
				sizeTexture.cx,
				sizeTexture.cy );

		if( !hTexture )
		{
			DEBUG_PRINT( 1, ("CreateGlyphTexture:  Couldn't create texture." ));
			bSuccess = false;
		}

	}

	// Don't need pixel data any more.
	if( pImageData )
	{
		delete[] pImageData;
		pImageData = NULL;
	}


	//return the success code
	return bSuccess;
}