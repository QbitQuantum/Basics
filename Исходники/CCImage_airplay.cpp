bool CCImage::_initWithPngData(void * pData, int nDatalen)
{
	IW_CALLSTACK("CCImage::_initWithPngData");
	
    bool bRet = false;
	
	s3eFile* pFile = s3eFileOpenFromMemory(pData, nDatalen);
	
	IwAssert(GAME, pFile);
	
	CIwImage    *image		= NULL;
	image = new CIwImage;
	
	image->ReadFile( pFile);
	
    s3eFileClose(pFile);
	
	// init image info
	m_bPreMulti	= true;
	m_bHasAlpha = image->HasAlpha();
	
	unsigned int bytesPerComponent = 3;
	if (m_bHasAlpha)
	{
		bytesPerComponent = 4;
	} 
	m_nHeight = (unsigned int)image->GetHeight();
	m_nWidth = (unsigned int)image->GetWidth();
	m_nBitsPerComponent = (unsigned int)image->GetBitDepth()/bytesPerComponent;
	
	tImageSource imageSource;
	
	imageSource.data    = (unsigned char*)pData;
	imageSource.size    = nDatalen;
	imageSource.offset  = 0;
	
	m_pData = new unsigned char[m_nHeight * m_nWidth * bytesPerComponent];
	
	unsigned int bytesPerRow = m_nWidth * bytesPerComponent;

	if(m_bHasAlpha)
	{
		unsigned char *src = NULL;
		src = (unsigned char *)image->GetTexels();
		
		unsigned char *tmp = (unsigned char *) m_pData;
		
		for(unsigned int i = 0; i < m_nHeight*bytesPerRow; i += bytesPerComponent)
		{
			*(tmp + i + 0)	=  (*(src + i + 0) * *(src + i + 3) + 1) >> 8;
			*(tmp + i + 1)	=  (*(src + i + 1) * *(src + i + 3) + 1) >> 8;					
			*(tmp + i + 2)	=  (*(src + i + 2) * *(src + i + 3) + 1) >> 8;
			*(tmp + i + 3)	=   *(src + i + 3);
		}
		
	}
	else
	{
		for (int j = 0; j < (m_nHeight); ++j)