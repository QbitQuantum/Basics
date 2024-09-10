//ÅÐ¶ÏBMP»òJPG²¢ÏÔÊ¾Í¼Ïñ
void CYangLiuImageProcess::ImageDisplay(CDC * pDC, double dZoom)
{
	IplImage *image = (IplImage*)voidImage;
	if (m_nOpenMode == 1) //BMP
	{
		StretchDIBits(pDC->m_hDC, 0, 0,
			int(dZoom*imageWidth + 0.5), int(dZoom* imageHeight + 0.5), 0, 0, imageWidth, imageHeight,
			m_pBits, lpbmi, DIB_RGB_COLORS, SRCCOPY);
	}
	if (m_nOpenMode == 2) //JPG
	{
		StretchDIBits(pDC->m_hDC, 0, 0, int(dZoom*image->width + 0.5), int(dZoom*image->height + 0.5),
			0, image->height, image->width, -image->height,
			image->imageData, lpbmi,
			DIB_RGB_COLORS, SRCCOPY);
	}
}