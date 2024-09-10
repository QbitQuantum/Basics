void
HippoCanvas::startTrackingHover()
{
    if (tooltip_->isShowing())
        return;

    // request a WM_MOUSEHOVER message; also resets the 
    // hover timer if we've already asked for this message.
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_HOVER;
    tme.hwndTrack = window_;
    // The default Windows tooltip delay is defined to be the 
    // double click time. We don't currently support 
    // it, but if we had a shorter delay when moving 
    // along a toolbar, that is defined as 1/5 double click 
    // time, and tooltips pop down by default after 10x double
    // click time. See docs for TTM_SETDELAYTIME for this.
    tme.dwHoverTime = GetDoubleClickTime();
    if (TrackMouseEvent(&tme) == 0) {
        g_warning("Failed to request mouse hover events");
    }
}