void TacticsInstrument_AppTrueWindAngle::DrawForeground(wxGCDC* dc)
{
	wxPoint points[4];
	double data;
	double val;
	double value;
	// The default foreground is the arrow used in most dials
	wxColour cl;
	GetGlobalColor(_T("DASH2"), &cl);
	wxPen pen1;
	pen1.SetStyle(wxSOLID);
	pen1.SetColour(cl);
	pen1.SetWidth(2);
	dc->SetPen(pen1);
	GetGlobalColor(_T("DASH1"), &cl);
	wxBrush brush1;
	brush1.SetStyle(wxSOLID);
	brush1.SetColour(cl);
	dc->SetBrush(brush1);
	dc->DrawCircle(m_cx, m_cy, m_radius / 8);

	/*True Wind*/
    if (!wxIsNaN(m_ExtraValueTrue)){  //m_ExtraValueTrue = True Wind Angle; we have a watchdog for TWS; if TWS becomes NAN, TWA must be NAN as well
      dc->SetPen(*wxTRANSPARENT_PEN);

      GetGlobalColor(_T("BLUE3"), &cl);
      wxBrush brush2;
      brush2.SetStyle(wxSOLID);
      brush2.SetColour(cl);
      dc->SetBrush(brush2);

      /* this is fix for a +/-180° round instrument, when m_MainValue is supplied as <0..180><L | R>
      * for example TWA & AWA */
      if (m_MainValueTrueUnit == _T("\u00B0L"))
        data = 360 - m_MainValueTrue;
      else
        data = m_MainValueTrue;

      // The arrow should stay inside fixed limits
      if (data < m_MainValueMin) val = m_MainValueMin;
      else if (data > m_MainValueMax) val = m_MainValueMax;
      else val = data;

      value = deg2rad((val - m_MainValueMin) * m_AngleRange / (m_MainValueMax - m_MainValueMin)) + deg2rad(m_AngleStart - ANGLE_OFFSET);

      points[0].x = m_cx + (m_radius * 0.95 * cos(value - .010));
      points[0].y = m_cy + (m_radius * 0.95 * sin(value - .010));
      points[1].x = m_cx + (m_radius * 0.95 * cos(value + .015));
      points[1].y = m_cy + (m_radius * 0.95 * sin(value + .015));
      points[2].x = m_cx + (m_radius * 0.22 * cos(value + 2.8));
      points[2].y = m_cy + (m_radius * 0.22 * sin(value + 2.8));
      points[3].x = m_cx + (m_radius * 0.22 * cos(value - 2.8));
      points[3].y = m_cy + (m_radius * 0.22 * sin(value - 2.8));
      dc->DrawPolygon(4, points, 0, 0);
    }
	/* Apparent Wind*/
    if (!wxIsNaN(m_ExtraValueApp)){ //m_ExtraValueApp=AWA; we have a watchdog for AWS; if AWS becomes NAN, AWA will also be NAN ...
      dc->SetPen(*wxTRANSPARENT_PEN);

      GetGlobalColor(_T("DASHN"), &cl);
      wxBrush brush;
      brush.SetStyle(wxSOLID);
      brush.SetColour(cl);
      dc->SetBrush(brush);

      /* this is fix for a +/-180° round instrument, when m_MainValue is supplied as <0..180><L | R>
      * for example TWA & AWA */
      if (m_MainValueAppUnit == _T("\u00B0L"))
        data = 360 - m_MainValueApp;
      else
        data = m_MainValueApp;

      // The arrow should stay inside fixed limits
      if (data < m_MainValueMin) val = m_MainValueMin;
      else if (data > m_MainValueMax) val = m_MainValueMax;
      else val = data;

      value = deg2rad((val - m_MainValueMin) * m_AngleRange / (m_MainValueMax - m_MainValueMin)) + deg2rad(m_AngleStart - ANGLE_OFFSET);

      points[0].x = m_cx + (m_radius * 0.95 * cos(value - .010));
      points[0].y = m_cy + (m_radius * 0.95 * sin(value - .010));
      points[1].x = m_cx + (m_radius * 0.95 * cos(value + .015));
      points[1].y = m_cy + (m_radius * 0.95 * sin(value + .015));
      points[2].x = m_cx + (m_radius * 0.22 * cos(value + 2.8));
      points[2].y = m_cy + (m_radius * 0.22 * sin(value + 2.8));
      points[3].x = m_cx + (m_radius * 0.22 * cos(value - 2.8));
      points[3].y = m_cy + (m_radius * 0.22 * sin(value - 2.8));
      dc->DrawPolygon(4, points, 0, 0);
    }
}