void CRRecentBookMenuItem::Draw( LVDrawBuf & buf, lvRect & rc, CRRectSkinRef skin, CRRectSkinRef valueSkin, bool selected )
{
    if ( !_book ) {
        CRMenuItem::Draw( buf, rc, skin, valueSkin, selected );
        return;
    }
    lvRect itemBorders = skin->getBorderWidths();
    skin->draw( buf, rc );
    buf.SetTextColor( 0x000000 );
    buf.SetBackgroundColor( 0xFFFFFF );
    int imgWidth = 0;
    int hh = rc.bottom - rc.top - itemBorders.top - itemBorders.bottom;
    if ( !_image.isNull() ) {
        int w = _image->GetWidth();
        int h = _image->GetHeight();
        buf.Draw( _image, rc.left + hh/2-w/2 + itemBorders.left, rc.top + hh/2 - h/2 + itemBorders.top, w, h );
        imgWidth = w + 8;
    }
    lvRect textRect = rc;
    textRect.left += imgWidth;

    lString16 author = _book->getAuthor();
    lString16 title = _book->getTitle();
    lString16 series = _book->getSeries();
    if ( title.empty() )
        title = _book->getFileName();
    else if ( !series.empty() )
        title << " - " << series;

    lvRect posRect = textRect;
    if ( !author.empty() ) {
        posRect.bottom = posRect.top + skin->getFont()->getHeight() + itemBorders.top + itemBorders.bottom;
        textRect.top = posRect.bottom - itemBorders.bottom;
        skin->drawText( buf, posRect, author );
    }
    if ( !title.empty() )
        valueSkin->drawText( buf, textRect, title );
}