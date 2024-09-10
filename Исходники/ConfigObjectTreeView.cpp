void ConfigObjectTreeView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	ShowScrollBar(SB_BOTH,FALSE);

	CRect rectClient;
	GetClientRect(rectClient);

	/*计算提示文本串“管理对象：”的文本高度，用于排列各控件*/
	int groupTextHeight = 0;
	if(objectTreeGroup.GetSafeHwnd() != NULL)
	{
		groupTextHeight = ControlLayoutHelper::CalculateHeaderTextHeight(objectTreeGroup);

		objectTreeGroup.SetWindowPos(NULL, 0, 0, rectClient.Width()+1, rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}

	int cyTlb = findToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	findToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top+groupTextHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

	if(configObjectTreeCtrl.GetSafeHwnd() != NULL)
	{
		configObjectTreeCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + groupTextHeight + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - groupTextHeight- cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
	}
}