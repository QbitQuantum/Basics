void AFXAPI _GetClippingCoordinates(LPCRECT pPosRect, LPCRECT pClipRect,
	LPRECT pIntersectRect, LPPOINT pOffsetPoint)
{
	int clipLeft = 0;
	int clipTop = 0;

	if ((pClipRect == NULL) || IsRectEmpty(pClipRect))
	{
		CopyRect(pIntersectRect, pPosRect);
	}
	else
	{
		IntersectRect(pIntersectRect, pPosRect, pClipRect);
		clipLeft = pClipRect->left;
		clipTop = pClipRect->top;
	}

	pOffsetPoint->x = min(0, pPosRect->left - clipLeft);
	pOffsetPoint->y = min(0, pPosRect->top - clipTop);
}