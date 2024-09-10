static QRectF qwtStrokedPathRect( 
    const QPainter *painter, const QPainterPath &path )
{
    QPainterPathStroker stroker;
    stroker.setWidth( painter->pen().widthF() );
    stroker.setCapStyle( painter->pen().capStyle() );
    stroker.setJoinStyle( painter->pen().joinStyle() );
    stroker.setMiterLimit( painter->pen().miterLimit() );

    QRectF rect;
    if ( qwtHasScalablePen( painter ) )
    {
        QPainterPath stroke = stroker.createStroke(path);
        rect = painter->transform().map(stroke).boundingRect();
    }
    else
    {
        QPainterPath mappedPath = painter->transform().map(path);
        mappedPath = stroker.createStroke( mappedPath );

        rect = mappedPath.boundingRect();
    }

    return rect;
}