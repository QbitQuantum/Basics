void CSkinDialog::OnNcMouseMove(CPoint point)
{
   	//获取窗体DC
	CWindowDC WndDc(this);
	//创建Graphics对象
	Graphics graph(WndDc.m_hDC);
	
	//设定鼠标进入标题栏
	if(!m_bMouseInTitileBar){
		TRACKMOUSEEVENT tme;
		tme.cbSize		= sizeof(tme);
		tme.hwndTrack	= m_hWnd;
		tme.dwFlags		= TME_LEAVE|TME_HOVER|TME_NONCLIENT;
		_TrackMouseEvent(&tme);  
		m_bMouseInTitileBar = true;
	}

	CRect rtButton;	
	CRect rtWnd;
	this->GetWindowRect(&rtWnd);

	//绘制退出按钮
	rtButton = m_rtBtnExt;
	rtButton.OffsetRect(rtWnd.left, rtWnd.top);
	if(rtButton.PtInRect(point)){	
		graph.DrawImage(m_bpBtnExtFocus,m_rtBtnExt.left,m_rtBtnExt.top,m_bpBtnExtFocus->GetWidth(),m_bpBtnExtFocus->GetHeight());
	}else{
		graph.DrawImage(m_bpBtnExt,m_rtBtnExt.left,m_rtBtnExt.top,m_bpBtnExt->GetWidth(),m_bpBtnExt->GetHeight());
	}

	//绘制最大化/恢复按钮
	rtButton = m_rtBtnMax;
	rtButton.OffsetRect(rtWnd.left, rtWnd.top);
	if(rtButton.PtInRect(point)){
		if(this->IsZoomed()){
			graph.DrawImage(m_bpBtnResFocus,m_rtBtnMax.left,m_rtBtnMax.top,m_bpBtnResFocus->GetWidth(),m_bpBtnResFocus->GetHeight());
		}else{
			graph.DrawImage(m_bpBtnMaxFocus,m_rtBtnMax.left,m_rtBtnMax.top,m_bpBtnMaxFocus->GetWidth(),m_bpBtnMaxFocus->GetHeight());
		}
	}else{
		if(this->IsZoomed()){
			graph.DrawImage(m_bpBtnRes,m_rtBtnMax.left,m_rtBtnMax.top,m_bpBtnRes->GetWidth(),m_bpBtnRes->GetHeight());
		}else{
			graph.DrawImage(m_bpBtnMax,m_rtBtnMax.left,m_rtBtnMax.top,m_bpBtnMax->GetWidth(),m_bpBtnMax->GetHeight());
		}
	}

	//绘制最小化按钮
	rtButton = m_rtBtnMin;
	rtButton.OffsetRect(rtWnd.left, rtWnd.top);
	if(rtButton.PtInRect(point)){	
		graph.DrawImage(m_bpBtnMinFocus,m_rtBtnMin.left,m_rtBtnMin.top,m_bpBtnMinFocus->GetWidth(),m_bpBtnMinFocus->GetHeight());
	}else{
		graph.DrawImage(m_bpBtnMin,m_rtBtnMin.left,m_rtBtnMin.top,m_bpBtnMin->GetWidth(),m_bpBtnMin->GetHeight());
	}

	return;
}