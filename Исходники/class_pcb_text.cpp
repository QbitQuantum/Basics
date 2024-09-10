void TEXTE_PCB::GetMsgPanelInfo( std::vector< MSG_PANEL_ITEM >& aList )
{
    wxString    msg;
    BOARD*      board;
    BOARD_ITEM* parent = (BOARD_ITEM*) m_Parent;

    wxASSERT( parent );

    if( parent->Type() == PCB_DIMENSION_T )
        board = (BOARD*) parent->GetParent();
    else
        board = (BOARD*) parent;

    wxASSERT( board );

    if( m_Parent && m_Parent->Type() == PCB_DIMENSION_T )
        aList.push_back( MSG_PANEL_ITEM( _( "DIMENSION" ), m_Text, DARKGREEN ) );
    else
        aList.push_back( MSG_PANEL_ITEM( _( "PCB Text" ), m_Text, DARKGREEN ) );

    aList.push_back( MSG_PANEL_ITEM( _( "Layer" ),
                                     board->GetLayerName( m_Layer ), BLUE ) );

    if( !m_Mirror )
        aList.push_back( MSG_PANEL_ITEM( _( "Mirror" ), _( "No" ), DARKGREEN ) );
    else
        aList.push_back( MSG_PANEL_ITEM( _( "Mirror" ), _( "Yes" ), DARKGREEN ) );

    msg.Printf( wxT( "%.1f" ), (float) m_Orient / 10 );
    aList.push_back( MSG_PANEL_ITEM( _( "Orientation" ), msg, DARKGREEN ) );

    msg = ::CoordinateToString( m_Thickness );
    aList.push_back( MSG_PANEL_ITEM( _( "Thickness" ), msg, MAGENTA ) );

    msg = ::CoordinateToString( m_Size.x );
    aList.push_back( MSG_PANEL_ITEM( _( "Size X" ), msg, RED ) );

    msg = ::CoordinateToString( m_Size.y );
    aList.push_back( MSG_PANEL_ITEM( _( "Size Y" ), msg, RED ) );
}