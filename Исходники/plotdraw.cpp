void wxPlotDrawerXAxis::Draw(wxDC *dc, bool refresh)
{
    wxCHECK_RET(dc, wxT("Invalid dc"));

    wxRect dcRect(GetDCRect());

    // Draw background
    if (refresh)
    {
        dc->SetBrush(m_backgroundBrush.GetBrush());
        dc->SetPen(*wxTRANSPARENT_PEN);
        dc->DrawRectangle(dcRect);
    }

    wxFont tickFont = m_tickFont;
    if (m_font_scale != 1)
        tickFont.SetPointSize( wxMax(2, RINT(tickFont.GetPointSize() * m_font_scale)) );

    dc->SetTextForeground( m_tickColour.GetColour() );
    dc->SetFont( tickFont );

    wxString label;

    // center the text in the window
    int x, y;
    dc->GetTextExtent(wxT("5"), &x, &y);
    int y_pos = (GetDCRect().height - y)/2 + 2; // FIXME I want to center this
    // double current = ceil(m_viewRect.GetLeft() / m_xAxisTick_step) * m_xAxisTick_step;
    int i, count = m_tickPositions.GetCount();
    for (i=0; i<count; i++)
    {
        dc->DrawText(m_tickLabels[i], m_tickPositions[i], y_pos);

//        if (!IsFinite(current, wxT("axis label is not finite")))
//            break;
//        label.Printf( m_xAxisTickFormat.c_str(), current );
//        dc->DrawText(label, m_xAxisTicks[i], y_pos);
//        current += m_xAxisTick_step;
    }

#ifdef DRAW_BORDERS
    // Test code for sizing to show the extent of the axes
    dc->SetBrush( *wxTRANSPARENT_BRUSH );
    dc->SetPen( *wxRED_PEN );
    dc->DrawRectangle(wxRect(wxPoint(0,0), clientSize));
#endif // DRAW_BORDERS
}