bool grib_pi::QualifyCtrlBarPosition( wxPoint position, wxSize size )
{   // Make sure drag bar (title bar) or grabber always screen
    bool b_reset_pos = false;
#ifdef __WXMSW__
    //  Support MultiMonitor setups which an allow negative window positions.
    //  If the requested window does not intersect any installed monitor,
    //  then default to simple primary monitor positioning.
    RECT frame_title_rect;
    frame_title_rect.left =  position.x;
    frame_title_rect.top =    position.y;
    frame_title_rect.right =  position.x + size.x;
    frame_title_rect.bottom = m_DialogStyle == ATTACHED_HAS_CAPTION ? position.y + 30 : position.y + size.y;


    if(NULL == MonitorFromRect(&frame_title_rect, MONITOR_DEFAULTTONULL))
        b_reset_pos = true;
#else
    wxRect window_title_rect;                    // conservative estimate
    window_title_rect.x = position.x;
    window_title_rect.y = position.y;
    window_title_rect.width = size.x;
    window_title_rect.height = m_DialogStyle == ATTACHED_HAS_CAPTION ? 30 : size.y;

    wxRect ClientRect = wxGetClientDisplayRect();
    if(!ClientRect.Intersects(window_title_rect))
        b_reset_pos = true;

#endif
    return !b_reset_pos;
}