void CCoorConvert::UpdateWindow()
{
    POINT ptDP1 = { m_ViewRect.right / 2, m_ViewRect.bottom / 2 };
    
    POINT ptDP2;
    LPToDP( m_ptMapCenter, ptDP2 );
    
    m_nOffsetX += ptDP1.x - ptDP2.x;
    m_nOffsetY += ptDP1.y - ptDP2.y;
    
    UpdateClipRect();
    m_nScaleValue = FLOAT_TO_LONG( DPIXELS_IN_METER / ( m_dScale * LPIXELS_IN_METER ) );
}