void TodoHandleItem::updateItem( const Bliss::Todo &todo )
{
  m_todo = todo;

  foreach( QGraphicsItem *child, childItems() ) {
    delete child;
  }

  if ( todo.type() == "group" ) {
    int circleSize = m_itemSize + 14;
    QGraphicsEllipseItem *groupCircle = new QGraphicsEllipseItem( this );
    groupCircle->setRect( -circleSize/2, -circleSize/2,
      circleSize, circleSize );
    QPen pen;
    pen.setBrush( Qt::white );
    pen.setWidth( 4 );
    groupCircle->setPen( pen );
  }
}