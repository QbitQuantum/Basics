CBitmap *CDataBase::convertToWin (NLMISC::CBitmap *pBitmap)
{
	CBitmap *pWinBitmap = new CBitmap;
	NLMISC::CObjectVector<uint8> &rPixel = pBitmap->getPixels();
	uint32 nNewWidth = pBitmap->getWidth()/WIDTH_DIVISOR;
	uint32 nNewHeight = pBitmap->getHeight()/HEIGHT_DIVISOR;
	uint8 *pNewPixel = new uint8[nNewHeight*nNewWidth*4];
	uint32 i, j;
	for (j = 0; j < nNewHeight; ++j)
	for (i = 0; i < nNewWidth; ++i)
	{
		pNewPixel[(i+j*nNewWidth)*4+0] = rPixel[(i*WIDTH_DIVISOR+j*HEIGHT_DIVISOR*pBitmap->getWidth())*4+2];
		pNewPixel[(i+j*nNewWidth)*4+1] = rPixel[(i*WIDTH_DIVISOR+j*HEIGHT_DIVISOR*pBitmap->getWidth())*4+1];
		pNewPixel[(i+j*nNewWidth)*4+2] = rPixel[(i*WIDTH_DIVISOR+j*HEIGHT_DIVISOR*pBitmap->getWidth())*4+0];
		pNewPixel[(i+j*nNewWidth)*4+3] = rPixel[(i*WIDTH_DIVISOR+j*HEIGHT_DIVISOR*pBitmap->getWidth())*4+3];
	}
	pWinBitmap->CreateBitmap (nNewWidth, nNewHeight, 1, 32, pNewPixel);	
	if (pNewPixel == NULL)
	{
		delete pWinBitmap;
		return NULL;
	}
	else
		return pWinBitmap;
}