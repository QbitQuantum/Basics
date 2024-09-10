void CDepartmentEstimationDialog::DrawBackground(CPaintDC &dc)
{
	CBrush brush(RGB(200,200,200));
	dc.FillRect(m_CanvasRect, &brush);
	brush.DeleteObject();
}