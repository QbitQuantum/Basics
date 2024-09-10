//--------------------------------------------------------------------------------------
// Name: NuiMenu::GetXYForVector()
// Desc: Map normalized space coordinates to screen space.
//--------------------------------------------------------------------------------------
XMFLOAT2 NuiMenu::GetXYForVector( FXMVECTOR vNormalizedSpace ) const
{
    assert( m_dwBackBufferWidth  > 0 );
    assert( m_dwBackBufferHeight > 0 );

    XMFLOAT2 rt;
    rt.x = XMVectorGetX( vNormalizedSpace ) * m_dwBackBufferWidth + m_dwBackBufferWidth;
    rt.y = m_dwBackBufferHeight - ( XMVectorGetY( vNormalizedSpace ) * m_dwBackBufferHeight / 2 + m_dwBackBufferHeight / 2 );

    return rt;
}