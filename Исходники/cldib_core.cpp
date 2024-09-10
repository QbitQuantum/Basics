/*!	\param hdc	Destination DC.
*	\param rectDest	Destination rectangle. If NULL, the DIB's 
*	  dimensions are used.
*	\param dib	DIB to blit.
*	\param rectSrc	Source rectangle. If NULL, the DIB's 
*	  dimensions is used.
*	\param flags	Blit flags.
*	\note	Tested for top-down and bottom-up DIB's
*/
int dib_to_hdc(HDC hdc, const RECT *rectDst, 
			CLDIB *dib, const RECT *rectSrc, DWORD flags)
{
	RECT dstR, srcR;
	int dibHa= dib_get_height(dib);

	if(rectDst == NULL)
		SetRect(&dstR, 0, 0, dib_get_width(dib), dibHa);
	else
		CopyRect(&dstR, rectDst);

	if(rectSrc == NULL)
		SetRect(&srcR, 0, 0, dib_get_width(dib), dibHa);
	else
		CopyRect(&srcR, rectSrc);

	int srcW= srcR.right-srcR.left, srcH= srcR.bottom-srcR.top;
	int dstW= dstR.right-dstR.left, dstH= dstR.bottom-dstR.top;

	SetStretchBltMode(hdc, COLORONCOLOR);
	return StretchDIBits( hdc, 
		dstR.left, dstR.bottom, dstW, -dstH, 
		srcR.left, dibHa-srcR.top, srcW, -srcH, 
		dib_get_img(dib), dib_get_info(dib), 
		DIB_RGB_COLORS, flags);	
}