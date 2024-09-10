//-----------------------------------------------------------------------------
// Deals with compressed channels
//-----------------------------------------------------------------------------
static void PSDReadCompressedChannels( CUtlBuffer &buf, int nChannelsCount, PSDMode_t mode, PSDPalette_t &palette, Bitmap_t &bitmap )
{
	unsigned char *pChannelRow = (unsigned char*)_alloca( bitmap.m_nWidth );
	for ( int i=0; i<nChannelsCount; ++i )
	{
		int nIndex = s_pChannelIndex[mode][i];
		Assert( nIndex != -1 );

		unsigned char *pDest = bitmap.m_pBits;
		for( int j=0; j < bitmap.m_nHeight; ++j )
		{
			unsigned char *pSrc = pChannelRow;
			unsigned int nPixelsRemaining = bitmap.m_nWidth;
			while ( nPixelsRemaining > 0 )
			{
				int nCount = buf.GetChar();
				if ( nCount >= 0 )
				{
					// If nCount is between 0 + 7F, it means copy the next nCount+1 bytes directly
					++nCount;
					Assert( (unsigned int)nCount <= nPixelsRemaining );
					buf.Get( pSrc, nCount );
				}
				else
				{
					// If nCount is between 80 and FF, it means replicate the next byte -Count+1 times
					nCount = -nCount + 1;
					Assert( (unsigned int)nCount <= nPixelsRemaining );
					unsigned char nPattern = buf.GetUnsignedChar();
					memset( pSrc, nPattern, nCount );
				}
				pSrc += nCount;
				nPixelsRemaining -= nCount;
			}
			Assert( nPixelsRemaining == 0 );

			// Collate the channels together
			for ( int k = 0; k < bitmap.m_nWidth; ++k, pDest += 4 )
			{
				pDest[nIndex] = pChannelRow[k];
			}
		}
	}

	PSDConvertToRGBA8888( nChannelsCount, mode, palette, bitmap );
}