// Create a DC representing the whole screen
wxScreenDC::wxScreenDC()
{
    m_macPort = CreateNewPort() ;
    GrafPtr port ;
    GetPort( &port ) ;
    SetPort( (GrafPtr) m_macPort ) ;
    Point pt = { 0,0 } ;
    LocalToGlobal( &pt ) ;     
    SetPort( port ) ;
    m_macLocalOrigin.x = -pt.h ;
    m_macLocalOrigin.y = -pt.v ;
#if wxMAC_USE_CORE_GRAPHICS
    m_macLocalOriginInPort = m_macLocalOrigin ;
#endif
    BitMap screenBits;
    GetQDGlobalsScreenBits( &screenBits );
    m_minX = screenBits.bounds.left ;

    SInt16 height ;
    GetThemeMenuBarHeight( &height ) ;
    m_minY = screenBits.bounds.top + height ;

    m_maxX = screenBits.bounds.right  ;
    m_maxY = screenBits.bounds.bottom ;

#if wxMAC_USE_CORE_GRAPHICS
    m_graphicContext = new wxMacCGContext( port ) ;    
#else
    MacSetRectRgn( (RgnHandle) m_macBoundaryClipRgn , m_minX , m_minY , m_maxX , m_maxY ) ;
    OffsetRgn( (RgnHandle) m_macBoundaryClipRgn , m_macLocalOrigin.x , m_macLocalOrigin.y ) ;
    CopyRgn( (RgnHandle) m_macBoundaryClipRgn , (RgnHandle) m_macCurrentClipRgn ) ;
#endif
    m_ok = TRUE ;    
}