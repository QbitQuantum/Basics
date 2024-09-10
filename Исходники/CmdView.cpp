void CmdView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值	
	///<brief 处理回退键
	if (VK_BACK == nChar){  ///<限制删除范围
		CPoint point;
		int num;
		num = myedit->GetLineCount();
		point = GetCaretPos();
		if (point.x <= HintPLen&&num - 1 == HintLine)
			return;
	}
	///<brief 处理回车键
	if (VK_RETURN == nChar) ///<处理回车消息
		DealEnter();
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}