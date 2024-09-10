static
bool maybeAddWindow(HWND hwnd, std::vector<QRect> *windows) {
    WINDOWINFO wi;
    GetWindowInfo( hwnd, &wi );
    RECT rect = wi.rcClient;

#if 0
    RECT rect;
    GetWindowRect( hwnd, &rect );
#endif

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // For some reason, rect.left and rect.top are shifted by cxWindowBorders and cyWindowBorders pixels respectively 
    // in *every* case (for every window), but cxWindowBorders and cyWindowBorders are non-zero only in the 
    // biggest-window case, therefore we need to save the biggest cxWindowBorders and cyWindowBorders to adjust the rect later
    cxWindowBorder = qMax(cxWindowBorder, wi.cxWindowBorders);
    cyWindowBorder = qMax(cyWindowBorder, wi.cyWindowBorders);

    if ( ( ( wi.dwStyle & WS_VISIBLE ) != 0 ) && (width >= minSize ) && (height >= minSize ) )
    {
        //QRect r( rect.left + 4, rect.top + 4, width, height); // 4 = max(wi.cxWindowBorders) = max(wi.cyWindowBorders)
        QRect r(rect.left + cxWindowBorder, rect.top + cyWindowBorder, width, height);
		if ( std::find( windows->begin(), windows->end(), r ) == windows->end() ) {
            windows->push_back( r );
            return true;
                }
    }
    return false;
}