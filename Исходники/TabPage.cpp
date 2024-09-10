//新增在切换页面时，若将tab大小改变，内部视图也随之变化，填充满tab控件的视图区
void CTabPage::ShowCurPage(UINT nShowState)
{
	int		nCurItem;
	TCITEM	itemCur;

	nCurItem		= GetCurSel();
	itemCur.mask	= TCIF_PARAM;

	GetItem(nCurItem, &itemCur);
	CWnd*	pWnd = (CWnd*)itemCur.lParam;

	CRect	rect;
	//获取标签页的坐标
	this->GetItemRect(0,&rect);
	int	nLeft  = rect.left;
	int	nTop = rect.bottom;
	//获取整个tab窗口坐标
	this->GetWindowRect(&rect);
	ScreenToClient(&rect);
	//将标签页以下的坐标作为起始位置
	rect.left = nLeft;
	rect.top = nTop;
	pWnd->MoveWindow(&rect);

	pWnd->ShowWindow(nShowState);
}