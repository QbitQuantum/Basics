bool CAutoPanParameters::NoHorzScroll(CWnd* pParentWnd) const
{
	DWORD dwStyle = pParentWnd->GetStyle();

	CScrollBar* pSBar = pParentWnd->GetScrollBarCtrl(SB_HORZ);

	INT MinPos, MaxPos;
	pParentWnd->GetScrollRange(SB_HORZ, &MinPos, &MaxPos);

	if (pParentWnd->GetScrollLimit(SB_HORZ) == 0) return true;
	if (MinPos == MaxPos) return true;
	if (pSBar != NULL && !pSBar->IsWindowEnabled()) return true;

	return false;
}