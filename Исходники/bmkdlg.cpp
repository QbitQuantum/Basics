void CRBookmarkMenuItem::Draw( LVDrawBuf & buf, lvRect & rc, CRRectSkinRef skin, CRRectSkinRef valueSkin, bool selected )
{
    _itemDirty = false;
    if ( !_bookmark ) {
        CRMenuItem::Draw( buf, rc, skin, valueSkin, selected );
        return;
    }
    lvRect itemBorders = skin->getBorderWidths();
    skin->draw( buf, rc );
    buf.SetTextColor( 0x000000 );
    buf.SetBackgroundColor( 0xFFFFFF );
    int imgWidth = DrawIcon( buf, rc, itemBorders );

    lvRect textRect = rc;
    textRect.left += imgWidth;
    lvRect posRect = textRect;
    lString16 text = _bookmark->getPosText();
    if ( !text.empty() ) {
        posRect.bottom = posRect.top + skin->getFont()->getHeight() + itemBorders.top + itemBorders.bottom;
        textRect.top = posRect.bottom - itemBorders.bottom;
    }
    lString16 postext(_("Page $1 ($2%)"));
    postext.replaceIntParam(1, _page+1);
    postext.replaceParam(2, lString16::itoa( _bookmark->getPercent()/100 ) << "." << fmt::decimal(_bookmark->getPercent()%100));
    postext << "  " << _bookmark->getTitleText();
    skin->drawText( buf, posRect, postext );
    if ( !text.empty() )
        valueSkin->drawText( buf, textRect, text );
}