void DSObjects::ExtractRects(REGION* pRegion)
{
	LPRGNDATA lpRgnData;

	DWORD sizeNeeed = GetRegionData((HRGN)pRegion->pOSRegion, 0, NULL); 

	lpRgnData = (LPRGNDATA)new char[sizeNeeed];
	DWORD returnValue = GetRegionData((HRGN)pRegion->pOSRegion, sizeNeeed, lpRgnData); 

	PN_VECTOR_DELETE(pRegion->rects);

	pRegion->numRects		= lpRgnData->rdh.nCount;
	pRegion->extents.left	= lpRgnData->rdh.rcBound.left;
	pRegion->extents.top	= lpRgnData->rdh.rcBound.top;
	pRegion->extents.right	= lpRgnData->rdh.rcBound.right;
	pRegion->extents.bottom	= lpRgnData->rdh.rcBound.bottom;
	
	if(lpRgnData->rdh.nCount)
	{
		pRegion->rects = new PNxRect[lpRgnData->rdh.nCount];

		// now extract the information.

		for(int j = 0; j < (int) lpRgnData->rdh.nCount;j++)
		{
			RECT* pRect = (RECT*)lpRgnData->Buffer;
			pRegion->rects[j].left = pRect[j].left;
			pRegion->rects[j].top = pRect[j].top;
			pRegion->rects[j].right = pRect[j].right;
			pRegion->rects[j].bottom = pRect[j].bottom;
		}
	}

	PN_VECTOR_DELETE(lpRgnData);
}