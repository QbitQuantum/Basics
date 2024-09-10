SCH_SHEET_PIN::SCH_SHEET_PIN( SCH_SHEET* parent, const wxPoint& pos, const wxString& text ) :
    SCH_HIERLABEL( pos, text, SCH_SHEET_PIN_T )
{
    SetParent( parent );
    wxASSERT( parent );
    m_Layer = LAYER_SHEETLABEL;
    m_Pos   = pos;

    if( parent->IsVerticalOrientation() )
        SetEdge( 2 );
    else
        SetEdge( 0 );

    m_shape = NET_INPUT;
    m_isDangling = true;
    m_number     = 2;
}