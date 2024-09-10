void CTwoOptDlg::OnPaint()
{	
	// device context for painting
	
	//CDC memDC ; // buffer context 
	CPaintDC dc(this);   

	if (IsIconic())
	{		
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);		
	}
	else
	{	
		if ( CoordsMatrix_.size() < 1 ) return;
	                              // device context for painting


		CPen penDot(PS_DOT,1,RGB(255,0,0));
		CPen penblack(PS_SOLID,3,RGB(0,0,0));

		CRect rect;
		GetClientRect(&rect);
	 

		int rectx1 = rect.left + 20;
		int rectx2 = rect.right  - 170;
		int recty1 = rect.top + 25;
		int recty2 = rect.bottom - bottom_limit;

		
		dc.Rectangle(rectx1-5,recty1-5,rectx2+5,recty2+5);
		// Plot each node
		size_t tour_size = CoordsMatrix_.size();
		for ( count = 0; count < tour_size; count++ )
		{
			Coords mat = CoordsMatrix_[count];
			xc1 =static_cast<int>(mat.GetX());
			yc1 = static_cast<int>(mat.GetY());

			xn1 = (float) ( xc1 - MinX ) / (float) ( MaxX - MinX );
			yn1 = (float) ( yc1 - MinY ) / (float) ( MaxY - MinY );
			xcoord1 = rectx1 + (int) (float) ( xn1 * abs( rectx1 - rectx2 ) );
			ycoord1 = recty2 - (int) (float) ( yn1 * abs( recty1 - recty2 ) );
			dc.SelectObject(&penblack);
			dc.Ellipse( xcoord1 - 2, ycoord1 - 2, xcoord1 + 2, ycoord1 + 2 );	

			//draw lines

			dc.SelectObject(&penDot);

			//draw last tour
			if ( hasRun && count < tour_size - 1 && m_lasttour.Tour.size())
			{
				m_lasttour.Tour[count];
				cc1 = static_cast<int>(m_lasttour.Tour[count]);
				cc2 =  static_cast<int>(m_lasttour.Tour[count +1]);
				DrawNodes(cc1 , cc2, rectx1, rectx2, recty2, recty1, dc);
			}

			dc.SelectObject(&penblack);
			if ( hasRun && count < tour_size - 1   && m_besttour.Tour.size())
			{
				cc1 =  static_cast<int>(m_besttour.Tour[count]);
				cc2 =  static_cast<int>(m_besttour.Tour[count +1]);
				DrawNodes(cc1 , cc2, rectx1, rectx2, recty2, recty1, dc);
			}
		

		}	

		// Draw final link
		if ( hasRun )
		{
			
			if(m_lasttour.Tour.size())
			{
				cc1 =  static_cast<int>(m_lasttour.Tour[tour_size-1]);
				cc2 = static_cast<int>( m_lasttour.Tour[0]);
				dc.SelectObject(&penDot);
				DrawNodes(cc1 , cc2, rectx1, rectx2, recty2, recty1, dc);
			}
			if(m_besttour.Tour.size())
			{
				dc.SelectObject(&penblack);
				cc1 =  static_cast<int>(m_besttour.Tour[tour_size-1]);
				cc2 =  static_cast<int>(m_besttour.Tour[0]);
				DrawNodes(cc1 , cc2, rectx1, rectx2, recty2, recty1, dc);
			}
			
		}
	
		CDialogEx::OnPaint();
	}
}