BOOL CJXCRetailOnlineDlg::PreTranslateMessage(MSG* pMsg)
{
	//设定时间内不允许处理消息
	if (!m_bAllowPretranslate)
	{
		return CBCGPDialog::PreTranslateMessage(pMsg);
	}

	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam) //按回车
	{
		CWnd* pWnd = GetFocus(); //焦点何处

		if (pWnd != NULL)
		{
			if (pWnd->GetDlgCtrlID() == IDC_EDIT_COMMODITYID)
			{
				if (QueryCommodity())//商品查询
				{
					m_bAllowPretranslate = FALSE;
					SetTimer(1001, 1000, NULL);
					return TRUE;
				}				
			}	
		}
	}

	if (WM_KEYDOWN == pMsg->message && VK_ESCAPE == pMsg->wParam )
	{
		GetParent()->GetParent()->PostMessage(WM_CLOSE);
	}

	return CNDDialog::PreTranslateMessage(pMsg);
}