wxSize wxChoice::DoGetBestSize() const
{
    int lbWidth = GetCount() > 0 ? 20 : 100;  // some defaults
    int lbHeight = 20;
    int wLine;
#if TARGET_CARBON
    long metric ;
    GetThemeMetric(kThemeMetricPopupButtonHeight , &metric );
    lbHeight = metric ;
#endif
    {
        wxMacPortStateHelper st( UMAGetWindowPort( (WindowRef) MacGetTopLevelWindowRef() ) ) ;
        if ( m_font.Ok() )
        {
            ::TextFont( m_font.MacGetFontNum() ) ;
            ::TextSize( m_font.MacGetFontSize() ) ;
            ::TextFace( m_font.MacGetFontStyle() ) ;
        }
        else
        {
            ::TextFont( kFontIDMonaco ) ;
            ::TextSize( 9  );
            ::TextFace( 0 ) ;
        }
        // Find the widest line
        for(int i = 0; i < GetCount(); i++) {
            wxString str(GetString(i));
        #if wxUSE_UNICODE
            Point bounds={0,0} ;
            SInt16 baseline ;
            ::GetThemeTextDimensions( wxMacCFStringHolder( str , m_font.GetEncoding() ) ,
                kThemeCurrentPortFont,
                kThemeStateActive,
                false,
                &bounds,
                &baseline );
            wLine = bounds.h ;
        #else
            wLine = ::TextWidth( str.c_str() , 0 , str.Length() ) ;
        #endif
            lbWidth = wxMax(lbWidth, wLine);
        }
        // Add room for the popup arrow
        lbWidth += 2 * lbHeight ;
        // And just a bit more
        int cx = ::TextWidth( "X" , 0 , 1 ) ;
        lbWidth += cx ;

    }
    return wxSize(lbWidth, lbHeight);
}