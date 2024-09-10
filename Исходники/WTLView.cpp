void CWTLView::DoPaint( CDCHandle dc )
{
    CRect      rc;
    SYSTEMTIME st;
    CString    sTime;
 
    // Get our window's client area.
    GetClientRect ( rc );
 
    // Build the string to show in the window.
    GetLocalTime ( &st );
    sTime.Format ( _T("The time is %d:%02d:%02d"), st.wHour, st.wMinute, st.wSecond );
 
    // Set up the DC and draw the text.
    dc.SaveDC();
 
	
    dc.SetBkColor ( RGB(255,153,0) );
    dc.SetTextColor ( RGB(0,0,0) );
    dc.ExtTextOut ( 0, 0, ETO_OPAQUE, rc, sTime, sTime.GetLength(), NULL );
 
    // Restore the DC.
    dc.RestoreDC(-1);

}