void DIMENSION::Mirror( const wxPoint& axis_pos )
{
    wxPoint newPos = m_Text.GetTextPosition();

#define INVERT( pos ) (pos) = axis_pos.y - ( (pos) - axis_pos.y )
    INVERT( newPos.y );

    m_Text.SetTextPosition( newPos );

    // invert angle
    m_Text.SetOrientation( -m_Text.GetOrientation() );

    INVERT( m_crossBarO.y );
    INVERT( m_crossBarF.y );
    INVERT( m_featureLineGO.y );
    INVERT( m_featureLineGF.y );
    INVERT( m_featureLineDO.y );
    INVERT( m_featureLineDF.y );
    INVERT( m_arrowG1F.y );
    INVERT( m_arrowG2F.y );
    INVERT( m_arrowD1F.y );
    INVERT( m_arrowD2F.y );
}