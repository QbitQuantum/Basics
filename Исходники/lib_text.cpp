void LIB_TEXT::drawGraphic( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aOffset,
                            COLOR4D aColor, GR_DRAWMODE aDrawMode, void* aData,
                            const TRANSFORM& aTransform )
{
    COLOR4D color = GetDefaultColor();

    if( aColor == COLOR4D::UNSPECIFIED )       // Used normal color or selected color
    {
        if( IsSelected() )
            color = GetItemSelectedColor();
    }
    else
    {
        color = aColor;
    }

    GRSetDrawMode( aDC, aDrawMode );

    /* Calculate the text orientation, according to the component
     * orientation/mirror (needed when draw text in schematic)
     */
    int orient = GetTextAngle();

    if( aTransform.y1 )  // Rotate component 90 degrees.
    {
        if( orient == TEXT_ANGLE_HORIZ )
            orient = TEXT_ANGLE_VERT;
        else
            orient = TEXT_ANGLE_HORIZ;
    }

    /* Calculate the text justification, according to the component
     * orientation/mirror this is a bit complicated due to cumulative
     * calculations:
     * - numerous cases (mirrored or not, rotation)
     * - the DrawGraphicText function recalculate also H and H justifications
     *      according to the text orientation.
     * - When a component is mirrored, the text is not mirrored and
     *   justifications are complicated to calculate
     * so the more easily way is to use no justifications ( Centered text )
     * and use GetBoundaryBox to know the text coordinate considered as centered
    */
    EDA_RECT bBox = GetBoundingBox();

    // convert coordinates from draw Y axis to libedit Y axis:
    bBox.RevertYAxis();
    wxPoint txtpos = bBox.Centre();

    // Calculate pos according to mirror/rotation.
    txtpos = aTransform.TransformCoordinate( txtpos ) + aOffset;

    EDA_RECT* clipbox = aPanel? aPanel->GetClipBox() : NULL;
    DrawGraphicText( clipbox, aDC, txtpos, color, GetShownText(), orient, GetTextSize(),
                     GR_TEXT_HJUSTIFY_CENTER, GR_TEXT_VJUSTIFY_CENTER, GetPenSize(),
                     IsItalic(), IsBold() );


    /* Enable this to draw the bounding box around the text field to validate
     * the bounding box calculations.
     */
#if 0
    // bBox already uses libedit Y axis.
    bBox = aTransform.TransformCoordinate( bBox );
    bBox.Move( aOffset );
    GRRect( clipbox, aDC, bBox, 0, LIGHTMAGENTA );
#endif
}