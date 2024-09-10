void LIB_BEZIER::drawGraphic( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aOffset,
                              void* aData, const TRANSFORM& aTransform )
{
    std::vector<wxPoint> PolyPointsTraslated;

    COLOR4D color   = GetLayerColor( LAYER_DEVICE );
    COLOR4D bgColor = GetLayerColor( LAYER_DEVICE_BACKGROUND );
    BEZIER_POLY converter( m_BezierPoints );
    converter.GetPoly( m_PolyPoints );

    PolyPointsTraslated.clear();

    for( unsigned int i = 0; i < m_PolyPoints.size() ; i++ )
        PolyPointsTraslated.push_back( aTransform.TransformCoordinate( m_PolyPoints[i] ) +
                                       aOffset );

    FILL_T fill = aData ? NO_FILL : m_Fill;

    EDA_RECT* const clipbox  = aPanel? aPanel->GetClipBox() : NULL;

    if( fill == FILLED_WITH_BG_BODYCOLOR )
    {
        GRPoly( clipbox, aDC, m_PolyPoints.size(), &PolyPointsTraslated[0], 1, GetPenSize(),
                bgColor, bgColor );
    }
    else if( fill == FILLED_SHAPE  )
    {
        GRPoly( clipbox, aDC, m_PolyPoints.size(), &PolyPointsTraslated[0], 1, GetPenSize(),
                color, color );
    }
    else
    {
        GRPoly( clipbox, aDC, m_PolyPoints.size(), &PolyPointsTraslated[0], 0, GetPenSize(),
                color, color );
    }
}