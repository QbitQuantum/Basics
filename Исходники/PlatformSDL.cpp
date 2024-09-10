BOOL CBPlatform::IntersectRect(LPRECT lprcDst, CONST LPRECT lprcSrc1, CONST LPRECT lprcSrc2)
{
	if (IsRectEmpty(lprcSrc1) || IsRectEmpty(lprcSrc2) ||
		lprcSrc1->left >= lprcSrc2->right || lprcSrc2->left >= lprcSrc1->right ||
		lprcSrc1->top >= lprcSrc2->bottom || lprcSrc2->top >= lprcSrc1->bottom)
	{
		SetRectEmpty(lprcDst);
		return FALSE;
	}
	lprcDst->left   = max(lprcSrc1->left, lprcSrc2->left);
	lprcDst->right  = min(lprcSrc1->right, lprcSrc2->right);
	lprcDst->top    = max(lprcSrc1->top, lprcSrc2->top);
	lprcDst->bottom = min(lprcSrc1->bottom, lprcSrc2->bottom);
	
	return TRUE;
}