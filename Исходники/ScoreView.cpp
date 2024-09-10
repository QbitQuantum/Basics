//重画函数
void CScoreView::OnPaint() 
{
	CPaintDC dc(this); 

	//设置 DC
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,0,0));
	dc.SelectObject(CSkinResourceManager::GetDefaultFont());

	//绘画背景
	CImageHandle ImageHandle(&m_ImageBack);
	m_ImageBack.BitBlt(dc,0,0);

	//显示分数
	CRect rcDraw;
	CString strScore ;
	char szBuffer[64] ;
	for (WORD i=0;i<CountArray(m_szUserName);i++)
	{
		if(lstrcmp(m_szUserName[i],""))
		{
			//字体颜色
			if ( m_lGameScore[i] > 0 )
				dc.SetTextColor( RGB( 255, 0, 0 ) ) ;
			else 
				dc.SetTextColor( RGB( 0, 0, 0 ) ) ;

			//用户名字
			rcDraw.left=10;
			rcDraw.right=130;
			rcDraw.top=i*23+80;
			rcDraw.bottom=rcDraw.top+12;
			dc.DrawText(m_szUserName[i],lstrlen(m_szUserName[i]),&rcDraw,DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_NOCLIP);

			//用户积分
			rcDraw.left=150;
			rcDraw.right=290;
			strScore.Format("%ld" , m_lGameScore[i]) ;
			//_snprintf(szBuffer,sizeof(szBuffer),TEXT("%ld"),m_lGameScore[i]);
			dc.DrawText(strScore,strScore.GetLength(),&rcDraw,DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_NOCLIP);
		}
	}

	if(0)
	{
		//显示税收
		rcDraw.left=10;
		rcDraw.right=130;
		rcDraw.top=4*23+80;
		rcDraw.bottom=rcDraw.top+12;
		LPCTSTR pszTax=TEXT("交易税");
		dc.DrawText(pszTax,lstrlen(pszTax),&rcDraw,DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_NOCLIP);

		//显示税收
		rcDraw.left=150;
		rcDraw.right=290;
		_snprintf(szBuffer,sizeof(szBuffer),"%ld",m_lGameTax);
		dc.DrawText(szBuffer,lstrlen(szBuffer),&rcDraw,DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_NOCLIP);
	}
	return;
}