void CImageDisp::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetCurrWindow();
	CVisionTab *pVTDlg = (CVisionTab*)GetParent();

	if(m_drawRect && !pVTDlg->clip && m_currWnd == RGB_WND) {
		m_drawRect=FALSE;
		m_clipEnd = point;

		// image clipping process
		CPoint vertex[4];
		vertex[0] = m_clipStart;
		vertex[1] = m_clipEnd;
		vertex[2] = CPoint(m_clipStart.x, m_clipEnd.y);
		vertex[3] = CPoint(m_clipEnd.x, m_clipStart.y);


		double dist = 0;
		double minV = sqrt((double)(vertex[0].x*vertex[0].x + vertex[0].y*vertex[0].y));
		double maxV = sqrt((double)(vertex[1].x*vertex[1].x + vertex[1].y*vertex[1].y));

		int imin = 0;
		int imax = 0;

		for(int i=0; i<sizeof(vertex)/sizeof(CPoint); i++)
		{
			dist = sqrt((double)(vertex[i].x*vertex[i].x + vertex[i].y*vertex[i].y));
			
			if(dist <= minV) {
				minV = dist;
				imin = i;
			}

			if(dist >= maxV) {
				maxV = dist;
				imax = i;
			}
		}
		
		m_clipStart = vertex[imin];
		m_clipEnd = vertex[imax];
		

		// Control창에 Clip image 좌표 출력
		// 변수 값 자체는 현재 picture control 좌표로 가지고 있고
		// 출력은 원래 이미지 사이즈(640x480)로 변환하여 출력한다. 
		CString str;
		str.Format("sx: %d, sy: %d, ex: %d, ey: %d", 
			(int)(m_clipStart.x/m_iZoom), (int)(m_clipStart.y/m_iZoom), (int)(m_clipEnd.x/m_iZoom), (int)(m_clipEnd.y/m_iZoom));
		pVTDlg->SetDlgItemTextA(IDC_CLIPCOORDINATE, str);
		
		// Console 출력
		/*printf("sx: %d, sy: %d, ex: %d, ey: %d\n", 
		m_clipStart.x, m_clipStart.y,
		m_clipEnd.x, m_clipEnd.y);*/
	} 
	

	CStatic::OnLButtonUp(nFlags, point);
}