bool scaleImage(CImage& srcImg,CImage& dstImg,int dstWidth,int dstHeight)
{
	int nHeight = srcImg.GetHeight();
	int nWidth = srcImg.GetWidth();
	
	if(dstImg.CreateEx(dstWidth,dstHeight, 24, BI_RGB))
	{
		HDC ImgDC = dstImg.GetDC();
		int nPreMode = ::SetStretchBltMode(ImgDC,  HALFTONE);
		srcImg.Draw(ImgDC, 0, 0, dstWidth,dstHeight, 0, 0, nWidth, nHeight);
		::SetBrushOrgEx(ImgDC, 0, 0, NULL); 
		::SetStretchBltMode(ImgDC, nPreMode);
		dstImg.ReleaseDC();
	}
	else
	{
		return false;
	}
	return true;
}