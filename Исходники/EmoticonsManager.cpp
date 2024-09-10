Emoticon::Emoticon(const tstring& _emoticonText, const string& _imagePath) : 
	emoticonText(_emoticonText), imagePath(_imagePath)
{
	emoticonBitmap = (HBITMAP) ::LoadImage(0, Text::toT(imagePath).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if(!emoticonBitmap)
		return;
	
	BITMAP bm = { 0 };
	GetObject(emoticonBitmap, sizeof(bm), &bm);
	
	if(bm.bmBitsPixel == 32) {
		BYTE *pBits = new BYTE[bm.bmWidth * bm.bmHeight * 4];
		GetBitmapBits(emoticonBitmap, bm.bmWidth * bm.bmHeight * 4, pBits);
		
		// fix alpha channel	
		for (int y = 0; y < bm.bmHeight; y++) {
			BYTE * pPixel = (BYTE *) pBits + bm.bmWidth * 4 * y;

			for (int x = 0; x < bm.bmWidth; x++) {
				pPixel[0] = pPixel[0] * pPixel[3] / 255; 
				pPixel[1] = pPixel[1] * pPixel[3] / 255; 
				pPixel[2] = pPixel[2] * pPixel[3] / 255; 

				pPixel += 4;
			}
		}
		SetBitmapBits(emoticonBitmap, bm.bmWidth * bm.bmHeight * 4, pBits);
	    
		delete[] pBits;
	}
}