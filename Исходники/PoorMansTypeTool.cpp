void CalcProxyScaleFactor (const VRect *filterRect, Rect *proxyRect, float *scaleFactor)
{

	short filterHeight;
	short filterWidth;
	short itemHeight;
	short itemWidth;
	Point fraction;

	shrinkRect (proxyRect, kGutter, kGutter); 		 // for the border

	filterHeight = (short)(filterRect->bottom - filterRect->top);
	filterWidth  = (short)(filterRect->right  - filterRect->left);
	
	itemHeight = proxyRect->bottom - proxyRect->top;
	itemWidth  = proxyRect->right  - proxyRect->left;
	
	if (itemHeight > filterHeight)
		itemHeight = filterHeight;
		
	if (itemWidth > filterWidth)
		itemWidth = filterWidth;
	
	fraction.h = (short)((filterWidth + itemWidth) / itemWidth);
	fraction.v = (short)((filterHeight + itemHeight) / itemHeight);

	// compute a scale factor now
	if (fraction.h > fraction.v) 
		*scaleFactor = ((float)filterWidth + (float)itemWidth) / (float)itemWidth;
	else
		*scaleFactor = ((float)filterHeight + (float)itemHeight) / (float)itemHeight;

	// resize the proxy rectangle
	copyRect (proxyRect, filterRect);	
	scaleRect (proxyRect, 1, (short)*scaleFactor);

	// now get a more precise scale factor from the resulting rectangle
	if (fraction.h > fraction.v) 
		*scaleFactor = (float)filterWidth / (float)(proxyRect->right  - proxyRect->left);
	else
		*scaleFactor = (float)filterHeight / (float)(proxyRect->bottom - proxyRect->top);

}