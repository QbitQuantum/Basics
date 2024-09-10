void COscillogram::OnMouseMove(UINT nFlags, CPoint point) 
{
	CStringArray valArray;
	CDWordArray colArray;
	CString     strVal;
	CRect		mRect;
	CClientDC	dc(this);
	float		length;		//鼠标位置绝对象素数
	float		gValue;
	int			oldMode;
	int			curCell;	//所在单元格
	CPen pen(PS_SOLID,0,RGB(0,0,0));
	BOOL		PtState = FALSE;

	//(整个函数过程的功能)计算所有线所在单元格的数值
	oldMode = dc.SetMapMode(MM_LOMETRIC);
	SetOscillogramRect(&dc);
	dc.SelectObject(&pen);
	dc.SetROP2(R2_NOTXORPEN);
	dc.DPtoLP(&point);

	//如果 鼠标不在波形图内 或者 没有曲线 不做处理返回
	if(!(point.x >= m_GridRect.left  && point.x <= m_GridRect.right+3
		&& point.y <= m_GridRect.top && point.y >= m_GridRect.bottom)
		|| GetCurveCount() < 1 || m_showTitle == FALSE)
	{
		if(m_bPt.x != -1)
		{
			DrawMouseLine(&dc,m_bPt);
			m_bPt =-1;
		}
		m_TitleTip.ShowWindow(SW_HIDE);
		return;
	}
	
	//绘画跟随鼠标的十字线
	if(m_bPt.x == -1)
	{
		m_bPt = point;
		DrawMouseLine(&dc,point);
	}
	else
	{	
		DrawMouseLine(&dc,m_bPt);
		m_bPt = point;
		DrawMouseLine(&dc,point);
	}

	//计算个单元格数值
	length  = (float)( point.x - m_GridRect.left );
	curCell = (int)( length / m_xSpan );
	
	if(!m_showTime)
	{
		float n1 = (m_xMaxVal - m_xMinVal)/(m_xCount-1);
		float n2 = m_xMinVal + curCell*n1;
		strVal.Format("%s: %.2f",m_xText,n2);
	}
	else
	{
		CTimeSpan m_xTimeSpan = 0;
		CTimeSpan sc    = m_endTime - m_beginTime;
		CTime	cnTime  = m_beginTime;
		
		double secCount = (sc.GetDays()*86400) + (sc.GetHours()*3600) + 
			(sc.GetMinutes()*60) + sc.GetSeconds();
		secCount = secCount / (m_xCount-1);
		
		int day    = (int)secCount/86400;	//天
		secCount  -= day*86400;
		int hour   = (int)secCount/3600;	//小时
		secCount  -= hour*3600;
		int minute = (int)secCount/60;		//分钟
		secCount  -= minute*60;
		int second = (int)secCount;			//秒
		m_xTimeSpan = CTimeSpan(day,hour,minute,second);

		for(int j=0;j<curCell;j++)
			cnTime += m_xTimeSpan;
		strVal.Format("%s: %s",m_xText,cnTime.Format("%Y/%m/%d  %H:%M:%S"));
	}
	colArray.Add(RGB(0,0,0));
	valArray.Add(strVal);

	for(int i=0;i<GetCurveCount();i++)
	{
		gValue = GetCurve(i)->ptVal.GetPointValue(curCell,PtState);
		
		if(PtState)
			strVal.Format("%s: %.2f",GetCurveName(i),gValue);
		else
			strVal.Format("%s: ",GetCurveName(i));
		colArray.Add(GetCurve(i)->lColor);
		valArray.Add(strVal);
	}

	//显示浮动窗体
	dc.LPtoDP(&point);
	dc.SetMapMode(oldMode);

	//窗口跟随鼠标位置移动
	GetClientRect(mRect);
	mRect.left   += CS_LMARGIN;
	mRect.top    += CS_LMARGIN;
	mRect.right  -= CS_LMARGIN;
	mRect.bottom -= CS_LMARGIN;
	ClientToScreen(&point);
	ClientToScreen(&mRect);

	m_TitleTip.SetParentRect(mRect);
	m_TitleTip.SetStrArray(valArray,colArray);
	m_TitleTip.SetPos(&point);
	ScreenToClient(&point);
	
	CWnd::OnMouseMove(nFlags, point);
}