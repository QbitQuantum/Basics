// Display the line on the screen!
void CDrawLine::Paint(CContext &dc,paint_options options)
{
	if (m_use_default_style)
	{
		switch (xtype)
		{
		case xWire:
			dc.SelectPen( PS_SOLID,1, m_pDesign->GetOptions()->GetUserColor().Get( CUserColor::WIRE ), options );
			break;
		case xBus:
			dc.SelectPen( PS_SOLID,5, m_pDesign->GetOptions()->GetUserColor().Get( CUserColor::BUS ), options );
			break;
		default:
			dc.SelectPen(m_pDesign->GetOptions()->GetStyle(m_style), options);
			break;
		}
	}
	else
	{
		dc.SelectPen(m_pDesign->GetOptions()->GetStyle(m_style), options);
	}

  dc.SetROP2(R2_COPYPEN);

  dc.MoveTo(m_point_a);

  if (!m_segment) {
	  switch (g_EditToolBar.m_DrawLineEdit.mode) {
		case 1: dc.LineTo(CDPoint(m_point_b.x,m_point_a.y));
			break;
		case 2:	dc.LineTo(CDPoint(m_point_a.x,m_point_b.y));
			break;
	  }
  }
  dc.LineTo(m_point_b);

  if (is_stuck)
  {
	  // Draw a nice circle to show the stickness...
	  dc.PaintConnectPoint( m_point_b );

	  // Do we need a junction
	  if (is_junction)
	  {
	    int js=JUNCTION_SIZE;
		CDPoint br,tl;
		br=CDPoint(m_point_b.x+js+1,m_point_b.y+js+1);
		tl=CDPoint(m_point_b.x-js,m_point_b.y-js);

		dc.SetROP2(R2_COPYPEN);

		dc.SelectPen(PS_SOLID,1,m_pDesign->GetOptions()->GetUserColor().Get( CUserColor::JUNCTION) );
		dc.SelectBrush(m_pDesign->GetOptions()->GetUserColor().Get( CUserColor::JUNCTION));
  	    dc.Ellipse(CDRect(tl.x,tl.y,br.x,br.y));
	  }
  }

}