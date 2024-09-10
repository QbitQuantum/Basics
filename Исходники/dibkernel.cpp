CDib::CDib(const CDib& dib,CRect rect)
//copy area of interest from dib
{
    int headerSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*dib.m_nColorTableEntries;
    //copy header
    m_lpBMIH = (LPBITMAPINFOHEADER) new char[headerSize];
    memcpy(m_lpBMIH,dib.m_lpBMIH,headerSize);
	//correct size
	m_lpBMIH->biWidth=rect.Width();
	m_lpBMIH->biHeight=rect.Height();
	m_lpBMIH->biSizeImage = 0;
    //compute member variables
    ComputeMetrics();
    ComputePaletteSize(dib.m_lpBMIH->biBitCount);
    MakePalette();
	m_pntOrigo = CPoint(0,0);	//default origo
    //copy bits
    m_lpImage = (LPBYTE)new char[m_dwSizeImage];
	for(int y=rect.top; y<=rect.bottom; y++){
		for(int x=rect.left; x<=rect.right; x++){
			SetPixel(CPoint(x-rect.left,y-rect.top),dib.GetPixel(CPoint(x,y)));
		}
	}
}