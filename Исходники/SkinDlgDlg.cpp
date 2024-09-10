void CSkinDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType != SIZE_MAXIMIZED)
	{
		CRect rc;
		GetClientRect(&rc);

		CRgn rgn;
		CPoint points[8] = { CPoint(rc.left, CORNER_SIZE), CPoint(CORNER_SIZE, rc.top),
			CPoint(rc.right - CORNER_SIZE, rc.top), CPoint(rc.right, CORNER_SIZE),
			CPoint(rc.right, rc.bottom - CORNER_SIZE - 1), CPoint(rc.right - CORNER_SIZE - 1, rc.bottom),
			CPoint(CORNER_SIZE + 1, rc.bottom), CPoint(rc.left, rc.bottom - CORNER_SIZE - 1) };
		int nPolyCounts[1] = { 8 };
		int dd = rgn.CreatePolyPolygonRgn(points, nPolyCounts, 1, WINDING);
		SetWindowRgn(rgn, TRUE);
	}
	else
	{
		SetWindowRgn(NULL, FALSE);
	}
	// TODO:  在此处添加消息处理程序代码
}