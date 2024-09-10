//-----------------------------------------------------------------------------
// Purpose: (virtual imp)
// Input  : pt - 
//			BOOL - 
// Output : int
//-----------------------------------------------------------------------------
int Clipper3D::HitTest( CPoint pt, BOOL )
{
    const int   POINT_TOLERANCE = 4;
    CRect       r;

    //
    // check point point 0
    //
    r.SetRect( m_ClipPoints[0][axHorz],
               m_ClipPoints[0][axVert],
               m_ClipPoints[0][axHorz],
               m_ClipPoints[0][axVert] );
    RectToScreen( r );
    r.InflateRect( POINT_TOLERANCE, POINT_TOLERANCE );
    if( r.PtInRect( pt ) )
    {
        return 0;
    }
    
    //
    // check clip point 1
    //
    r.SetRect( m_ClipPoints[1][axHorz],
               m_ClipPoints[1][axVert],
               m_ClipPoints[1][axHorz],
               m_ClipPoints[1][axVert] );
    RectToScreen( r );
    r.InflateRect( POINT_TOLERANCE, POINT_TOLERANCE );
    if( r.PtInRect( pt ) )
    {
        return 1;
    }

    // neither point hit
    return -1;
}