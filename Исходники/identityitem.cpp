void IdentityItem::updateItem( const Polka::Identity &identity )
{
  m_identity = identity;

  foreach( QGraphicsItem *child, childItems() ) {
    delete child;
  }

  if ( identity.type() == "group" ) {
    int circleSize = m_itemSize + 14;
    QGraphicsEllipseItem *groupCircle = new QGraphicsEllipseItem( this );
    groupCircle->setRect( -circleSize/2, -circleSize/2,
      circleSize, circleSize );
    QPen pen;
    pen.setBrush( Qt::white );
    pen.setWidth( 4 );
    groupCircle->setPen( pen );
  }

  QPixmap pixmap = m_model->pixmap( identity );

  QGraphicsItem *item = new QGraphicsPixmapItem( pixmap, this );
  item->setPos( -pixmap.width() / 2, -pixmap.height() / 2 );

  QGraphicsTextItem *textItem = new QGraphicsTextItem( identity.name().value() );

  int textWidth = textItem->boundingRect().width();
  int textHeight = textItem->boundingRect().height();

  m_nameItem = new RoundedRectItem( this );
  m_nameItem->setRect( 0, 0, textWidth, textHeight );
  m_nameItem->setBrush( QColor( 255,255,230 ) );
  m_nameItem->setZValue( 10 );

  textItem->setParentItem( m_nameItem );

  m_nameItem->setPos( - textWidth / 2, 30 );

  m_fanMenu = new FanMenu( this );
  m_fanMenu->setZValue( 50 );

  FanMenuItem *menuItem = m_fanMenu->addItem( i18n("Remove") );
  connect( menuItem, SIGNAL( clicked() ), SLOT( emitRemoveIdentity() ) );
  m_checkMenuItem = m_fanMenu->addItem( i18n("Check") );
  connect( m_checkMenuItem, SIGNAL( clicked() ), SLOT( checkItem() ) );
  if ( identity.type() == "group" ) {
    menuItem = m_fanMenu->addItem( i18n("Go to") );
  } else {
    menuItem = m_fanMenu->addItem( i18n("Show") );
  }
  connect( menuItem, SIGNAL( clicked() ), SLOT( emitShowIdentity() ) );
  m_fanMenu->setupItems();

  hidePopups();
}