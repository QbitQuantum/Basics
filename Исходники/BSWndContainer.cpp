///////////////////////////////////////////////////
// full screen
void CBSWndContainer::SetFullScreen(BOOL bFlag)
{
	if(bFlag==m_bFullScreen) return;

	if( bFlag )
	{//全屏
// 		//得到显示器分辨率
// 		int cx=GetSystemMetrics(SM_CXSCREEN);
// 		int cy=GetSystemMetrics(SM_CYSCREEN);
// 
// 		//保存位置信息
// 		GetWindowPlacement(&_temppl);
// 		//修改风格
// 		ModifyStyle(WS_CHILD,WS_POPUP);
// 		//修改父窗口
// 		_tempparent=SetParent(NULL);
// 		_tempparent->ShowWindow(SW_HIDE);


		//移动窗口
/*		MoveWindow(0,0,cx,cy);*/

		ModifyStyle(WS_CHILD,WS_POPUP);
 		//修改父窗口
//  		_tempparent=SetParent(NULL);
//  		_tempparent->ShowWindow(SW_HIDE);
		GetWindowPlacement(&m_OldWndPlacement); 
		CRect WindowRect; 
		GetWindowRect(&WindowRect); 
		CRect ClientRect; 
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect); 
		ClientToScreen(&ClientRect); 
		// 获取屏幕的分辨率 
		CRect screenRect;
		GetCurrentScreenMonitorRect(m_hWnd, screenRect);
		int nFullWidth = screenRect.Width(); //GetSystemMetrics(SM_CXSCREEN); 
		int nFullHeight = screenRect.Height(); //GetSystemMetrics(SM_CYSCREEN); 
		//将除控制条外的客户区全屏显示到从(0,0)到(nFullWidth, nFullHeight)区域, 将(0,0)和(nFullWidth, nFullHeight)两个点外扩充原窗口和除控制条之外的 客户区位置间的差值, 就得到全屏显示的窗口位置 
		m_FullScreenRect.left= WindowRect.left - ClientRect.left + screenRect.left;
		m_FullScreenRect.top = WindowRect.top - ClientRect.top + screenRect.top;
		m_FullScreenRect.right = m_FullScreenRect.left + WindowRect.right - ClientRect.right + nFullWidth;//::GetSystemMetrics(SM_CXSCREEN);
		m_FullScreenRect.bottom = m_FullScreenRect.top + WindowRect.bottom - ClientRect.bottom + nFullHeight;//::GetSystemMetrics(SM_CYSCREEN);
		
		m_bFullScreen=TRUE; // 设置全屏显示标志为 TRUE 
		// 进入全屏显示状态 
		WINDOWPLACEMENT wndpl; 
		wndpl.length=sizeof(WINDOWPLACEMENT); 
		wndpl.flags=0; 
		wndpl.showCmd=SW_SHOWNORMAL; 
		wndpl.rcNormalPosition= m_FullScreenRect; 
		_tempparent=SetParent(NULL);
 		_tempparent->ShowWindow(SW_HIDE);
		SetWindowPlacement(&wndpl);
	//	SetWindowPos(&wndTopMost,0,0,cx,cy,NULL);
	}
	else
	{//还原
		//还原父窗口
// 		_tempparent->ShowWindow(SW_SHOW);
// 		SetParent(_tempparent);
// 		//还原风格
// 		ModifyStyle(WS_POPUP,WS_CHILD);
// 		//还原位置
// 		SetWindowPlacement(&_temppl);
		_tempparent->ShowWindow(SW_SHOW);
		SetParent(_tempparent);
		//还原风格
		ModifyStyle(WS_POPUP,WS_CHILD);
		SetWindowPlacement(&m_OldWndPlacement);
	}

	m_bFullScreen=bFlag;
	Invalidate();
}