void CStackWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CFont* pOldFont = dc.SelectObject(&m_Font);
	pOldFont->DeleteObject();
	
	RECT rc;
	GetClientRect(&rc);

	DWORD dwSelStart = std::min(m_dwSelStart,m_dwSelEnd);
	DWORD dwSelEnd = std::max(m_dwSelStart,m_dwSelEnd);

	for (int i=0;i*m_nLineHight<=rc.bottom;++i)
	{
		RECT tmp = rc;
		tmp.top = i*m_nLineHight;
		tmp.bottom = tmp.top + m_nLineHight;
			

		DWORD data;
		DWORD dwLineAddr = m_dwStartAddr+i*4;
		SIZE_T nRead = 0;

		if (dwLineAddr>=dwSelStart && dwLineAddr <=dwSelEnd)
		{
			dc.SetBkColor(0x00FF0000);
		}

		if (debug_kernel_ptr && debug_kernel_ptr->read_memory(dwLineAddr,&data,4,&nRead) && nRead == 4)
		{
			char line[20];
			sprintf(line,"%08X %08X",dwLineAddr,data);
			dc.ExtTextOut(0,i*m_nLineHight,ETO_OPAQUE,&tmp,line,17,NULL);
		}
		else
		{
			char line[20];
			sprintf(line,"%08X ???",dwLineAddr);
			dc.ExtTextOut(0,i*m_nLineHight,ETO_OPAQUE,&tmp,line,12,NULL);
		}

		dc.SetBkColor(0x00FFFFFF);
	}
	// 不为绘图消息调用 CWnd::OnPaint()
}