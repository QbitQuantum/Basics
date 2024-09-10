void GRolloverButton::hoverMoveEvent( QGraphicsSceneHoverEvent *e )
{
    GLabelItem::hoverMoveEvent( e );
    setCursor( QCursor( Qt::PointingHandCursor ) );
}