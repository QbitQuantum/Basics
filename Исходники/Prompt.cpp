//重画函数
void CPrompt::OnPaint() 
{
	CPaintDC dc(this); 

	//设置 DC
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	dc.SelectObject(CSkinResourceManager::GetDefaultFont());

	//创建字体
	CFont ViewFont;
	ViewFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,1,TEXT("Arial"));
	CFont *pOldFont=dc.SelectObject(&ViewFont);

	CRect rcScore(0,30,220,30+19);
	dc.DrawText(m_tStr,lstrlen(m_tStr),&rcScore,DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);

	//还原字体
	dc.SelectObject(pOldFont);
	ViewFont.DeleteObject();

	return;
}