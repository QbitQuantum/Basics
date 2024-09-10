void LIB_FIELD::drawGraphic( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aOffset,
                             void* aData, const TRANSFORM& aTransform )
{
    wxPoint  text_pos;
    COLOR4D  color = IsVisible() ? GetDefaultColor() : GetInvisibleItemColor();
    int      linewidth = GetPenSize();

    text_pos = aTransform.TransformCoordinate( GetTextPos() ) + aOffset;

    wxString text;

    if( aData )
        text = *(wxString*)aData;
    else
        text = m_Text;

    EDA_RECT* clipbox = aPanel? aPanel->GetClipBox() : NULL;

    DrawGraphicText( clipbox, aDC, text_pos, color, text, GetTextAngle(), GetTextSize(),
                     GetHorizJustify(), GetVertJustify(), linewidth, IsItalic(), IsBold() );
}