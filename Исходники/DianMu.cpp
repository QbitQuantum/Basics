void CDianMu::OnPaint()
{
	CPaintDC dc(this); 
	//SetWindowPos(&wndBottom,0,0,242,137,SWP_NOZORDER);
	CGameImageHelper handle(&m_bk);
	handle.BitBlt(dc,0,0);
	dc.SetBkMode(TRANSPARENT);

	CFont font; //JMod-字体格式修改-20090631
	font.CreateFont(-12,0,0,0,400,NULL,NULL,NULL,134,3,2,1,2,TEXT("宋体"));
	CFont *pOldFont = dc.SelectObject(&font);	
	dc.TextOut(m_iDestX,m_iDestY,m_strMessage);
	dc.SelectObject(pOldFont);
	font.DeleteObject();

	//jph 100127
	HRGN hRgn;
	hRgn=AFCBmpToRgn(m_bk,RGB(255,0,255),RGB(1,1,1));
	if(hRgn)
	{
		SetWindowRgn(hRgn,true);
	}

}