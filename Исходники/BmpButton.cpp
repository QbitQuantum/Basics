//设置背景位图，设置的位图资源由调用者负责释放
void CBmpButton::SetStateBitmap(CBitmap *p_pUncheckedBmpNormal, CBitmap *p_pUncheckedBmpSelect,
								 CBitmap *p_pBmpUncheckedOver, CBitmap *p_pBmpDisable,
								 CBitmap *p_pCheckedBmpNormal, CBitmap *p_pCheckedBmpSelect,
								 CBitmap *p_pBmpCheckedOver)
{
	ASSERT(p_pUncheckedBmpNormal);

	m_pBmpUncheckedNormal = p_pUncheckedBmpNormal;
	m_pBmpUncheckedSelect = p_pUncheckedBmpSelect;
	m_pBmpUncheckedOver = p_pBmpUncheckedOver;
	
	m_pBmpCheckedNormal = p_pCheckedBmpNormal;
	m_pBmpCheckedSelect = p_pCheckedBmpSelect;
	m_pBmpCheckedOver = p_pBmpCheckedOver;
	
	m_pBmpDisable = p_pBmpDisable;

	m_bBmpIsCreateBySelf = FALSE;
	
	///////////////////////////////
	BITMAP BmpInfo;
	p_pUncheckedBmpNormal->GetBitmap(&BmpInfo);

	CRect rcBtnRect;
	CWnd *pWnd = this->GetParent();
	GetWindowRect(&rcBtnRect);
	pWnd->ScreenToClient(rcBtnRect);

	rcBtnRect.right = rcBtnRect.left + BmpInfo.bmWidth;
	rcBtnRect.bottom = rcBtnRect.top + BmpInfo.bmHeight;


	MoveWindow(rcBtnRect);
}