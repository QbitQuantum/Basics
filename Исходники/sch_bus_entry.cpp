EDA_RECT SCH_BUS_ENTRY::GetBoundingBox() const
{
    EDA_RECT box;

    box.SetOrigin( m_pos );
    box.SetEnd( m_End() );

    box.Normalize();
    int width = ( m_width == 0 ) ? GetDefaultLineThickness() : m_width;
    box.Inflate( width / 2 );

    return box;
}