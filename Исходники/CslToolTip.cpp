void CslToolTip::OnEraseBackground(wxEraseEvent& event)
{
    if (!m_frame)
        return;

    wxDC& dc=*event.GetDC();
#else
void CslToolTip::OnPaint(wxPaintEvent& event)
{
    if (!m_frame)
        return;

    wxPaintDC dc(m_frame);
#endif
    wxInt32 w=0,h=0;
    m_frame->GetClientSize(&w,&h);

#ifdef __WXMAC__
    dc.SetPen(*wxTRANSPARENT_PEN);
#else
    dc.SetPen(wxPen(SYSCOLOUR(wxSYS_COLOUR_INFOTEXT)));
#endif
    dc.SetBrush(wxBrush(SYSCOLOUR(wxSYS_COLOUR_INFOBK)));

    dc.Clear();
#ifdef __WXMAC__
    dc.DrawRectangle(0,0,w,h);
#else
    dc.DrawRoundedRectangle(0,0,w,h,2.0);
#endif
}

void CslToolTip::OnTimer(wxTimerEvent& WXUNUSED(event))
{
    if (!m_parent)
        return;

    if (m_top)
    {
        ResetTip();
        return;
    }

    CreateFrame();
}

void CslToolTip::OnMouseLeave(wxMouseEvent& event)
{
    if (m_frame && event.GetEventObject()==m_frame)
    {
        const wxSize& size=m_frame->GetClientSize();
        const wxPoint& pos=event.GetPosition();

        if (pos.x>=size.x || pos.y>=size.y || pos.x<=0 || pos.y<=0)
            ResetTip();
    }

    event.Skip();
}

void CslToolTip::OnMouseButton(wxMouseEvent& event)
{
    ResetTip();

    event.Skip();
}