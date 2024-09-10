void COverallDataView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_masterSurveyList.GetLegQuery()!=NULL)
	{
		CRect r;
		CBrush brush;
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_QUESTIONBRUSH);
		brush.CreatePatternBrush(&bitmap);
		GetClientRect(r);
		dc.FillRect(r,&brush);
	}
}