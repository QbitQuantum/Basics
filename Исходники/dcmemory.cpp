void wxMemoryDC::DoSelect( const wxBitmap& bitmap )
{
    if ( m_selected.Ok() )
    {
#if wxMAC_USE_CORE_GRAPHICS
        m_selected.EndRawAccess() ;
        delete m_graphicContext ;
        m_graphicContext = NULL ;
#else
// TODO: UnlockPixels( GetGWorldPixMap(MAC_WXHBITMAP(m_selected.GetHBITMAP())) );
#endif
    }

    m_selected = bitmap;
    if (m_selected.Ok())
    { 
#if wxMAC_USE_CORE_GRAPHICS
        if ( m_selected.GetDepth() != 1 )
            m_selected.UseAlpha() ;
        m_selected.BeginRawAccess() ;
		m_width = bitmap.GetWidth();
		m_height = bitmap.GetHeight();
        CGColorSpaceRef genericColorSpace  = wxMacGetGenericRGBColorSpace();
        CGContextRef bmCtx = (CGContextRef) m_selected.GetHBITMAP();

        if ( bmCtx )
        {
            CGContextSetFillColorSpace( bmCtx, genericColorSpace );
            CGContextSetStrokeColorSpace( bmCtx, genericColorSpace );
			SetGraphicsContext( wxGraphicsContext::CreateFromNative( bmCtx ) );
        }
        m_ok = (m_graphicContext != NULL) ;

#else
        m_macPort = m_selected.GetHBITMAP( &m_macMask ) ;
        m_ok = (m_macPort != NULL) ;
        if (m_ok)
        {
            LockPixels( GetGWorldPixMap( (CGrafPtr) m_macPort ) ) ;
            SetRectRgn( (RgnHandle) m_macBoundaryClipRgn , 0 , 0 , m_selected.GetWidth() , m_selected.GetHeight() ) ;
            CopyRgn( (RgnHandle) m_macBoundaryClipRgn , (RgnHandle) m_macCurrentClipRgn ) ;
        }
#endif
    }
    else
    {
        m_ok = false;
    }
}