void EDA_RECT::Merge( const EDA_RECT& aRect )
{
    Normalize();        // ensure width and height >= 0
    EDA_RECT rect = aRect;
    rect.Normalize();   // ensure width and height >= 0
    wxPoint  end = GetEnd();
    wxPoint  rect_end = rect.GetEnd();

    // Change origin and size in order to contain the given rect
    m_Pos.x = std::min( m_Pos.x, rect.m_Pos.x );
    m_Pos.y = std::min( m_Pos.y, rect.m_Pos.y );
    end.x   = std::max( end.x, rect_end.x );
    end.y   = std::max( end.y, rect_end.y );
    SetEnd( end );
}