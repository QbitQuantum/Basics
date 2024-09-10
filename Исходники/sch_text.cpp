EDA_RECT SCH_TEXT::GetBoundingBox() const
{
    // We must pass the effective text thickness to GetTextBox
    // when calculating the bounding box
    int linewidth = ( m_Thickness == 0 ) ? GetDefaultLineThickness() : m_Thickness;

    linewidth = Clamp_Text_PenSize( linewidth, m_Size, m_Bold );

    EDA_RECT rect = GetTextBox( -1, linewidth );

    if( m_Orient )                          // Rotate rect
    {
        wxPoint pos = rect.GetOrigin();
        wxPoint end = rect.GetEnd();
        RotatePoint( &pos, m_Pos, m_Orient );
        RotatePoint( &end, m_Pos, m_Orient );
        rect.SetOrigin( pos );
        rect.SetEnd( end );
    }

    rect.Normalize();
    return rect;
}