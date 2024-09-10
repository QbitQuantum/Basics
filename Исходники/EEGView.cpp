void CEEGView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CRect rect;
	GetClientRect(rect);

	CSize sizeTotal;

	CCoreModelDoc* pDoc = (CCoreModelDoc*)GetDocument();

	CString path = pDoc->GetCurUser()+_T("\\")+_T(VIEWFILE);
	CViewerConfig viewconfig(path);
	if (!viewconfig.IsOpen())			//未打开文件
	{
		m_wndOutput << "未加载EEG Viewer" << m_EndOut;
		sizeTotal.cx = 100;
		sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}
	else
	{
		if (!viewconfig.LoadFileMsg())
			m_wndOutput << "无法读取文件：" << path << " 内容" << m_EndOut;
		viewconfig.CloseFile();

		CString name = L"";
		if (viewconfig.GetSelDllPath().ReverseFind('\\') == -1)
		{
			name = viewconfig.GetSelDllPath();
		}
		else
		{
			name = viewconfig.GetSelDllPath().Right(viewconfig.GetSelDllPath().GetLength() - 1 -
				viewconfig.GetSelDllPath().ReverseFind('\\'));	//获得dll名称
		}

		int len, width;
		len = viewconfig.GetWindowLength();
		width = viewconfig.GetWindowWidth();
		// TODO:  计算此视图的合计大小
		sizeTotal.cx = len;
		sizeTotal.cy = width*pDoc->GetChanNum();
		SetScrollSizes(MM_TEXT, sizeTotal);
		if (!pDoc->RegEEGViewer(viewconfig.GetSelDllPath(), this))
			m_wndOutput << "加载EEG Viewer:" << name << "失败" << m_EndOut;
		else
		{
			m_wndOutput << "加载EEG Viewer:" << name << "成功" << m_EndOut;
			CBaseEEGViewerWnd* pEEGView = pDoc->GetEEGViewer();
			int maxv, minv;
			if (viewconfig.GetIsAutoMaxMin())
				pEEGView->AutoMaxMin(true);										//自动调整显示幅度
			else
			{
				pEEGView->AutoMaxMin(false);
				maxv = viewconfig.GetMaxValue();
				minv = viewconfig.GetMinValue();
				pEEGView->SetMaxMin(maxv, minv);
			}
		}
	}

	CBaseEEGViewerWnd* pEEGView = pDoc->GetEEGViewer();
	if (!pEEGView)
	{
		m_wndOutput << "EEG Viewer为空，无效" << m_EndOut;
		return;
	}

	rect.right = sizeTotal.cx;
	rect.bottom = sizeTotal.cy;
	pEEGView->MoveWindow(rect);
}