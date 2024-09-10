void LIB_CIRCLE::drawGraphic( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aOffset,
                              void* aData, const TRANSFORM& aTransform )
{
    wxPoint pos1    = aTransform.TransformCoordinate( m_Pos ) + aOffset;
    COLOR4D color   = GetLayerColor( LAYER_DEVICE );
    COLOR4D bgColor = GetLayerColor( LAYER_DEVICE_BACKGROUND );
    FILL_T  fill    = aData ? NO_FILL : m_Fill;

    EDA_RECT* const clipbox  = aPanel? aPanel->GetClipBox() : NULL;

    if( fill == FILLED_WITH_BG_BODYCOLOR )
        GRFilledCircle( clipbox, aDC, pos1.x, pos1.y, m_Radius, GetPenSize(), bgColor, bgColor );
    else if( fill == FILLED_SHAPE )
        GRFilledCircle( clipbox, aDC, pos1.x, pos1.y, m_Radius, 0, color, color );
    else
        GRCircle( clipbox, aDC, pos1.x, pos1.y, m_Radius, GetPenSize(), color );
}