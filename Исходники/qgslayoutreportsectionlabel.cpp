void QgsLayoutReportSectionLabel::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget * )
{
  if ( !mLayout || !mLayout->renderContext().isPreviewRender() )
  {
    //don't draw label in outputs
    return;
  }

  if ( mLabel.isEmpty() )
    return;

  QFont f;
  f.setPointSizeF( 8 );
  QFontMetrics fm( f );
  QSize s = fm.size( 0, mLabel );
  double margin = fm.height() / 5.0;

  double scaleValue = scale() / painter->transform().m11();
  painter->save();
  painter->setRenderHint( QPainter::Antialiasing, true );
  painter->scale( scaleValue, scaleValue );
  QRectF r = rect();
  QRectF scaledRect( r.left() / scaleValue, r.top() / scaleValue, r.width() / scaleValue, r.height() / scaleValue );

  if ( scaledRect.width() < s.width() + 2 * margin || scaledRect.height() < s.height() + 2 * margin )
  {
    // zoomed out too far to fully draw label inside item rect
    return;
  }

  QRectF textRect = QRectF( scaledRect.left() + margin, scaledRect.top() + margin, scaledRect.width() - 2 * margin, scaledRect.height() - 2 * margin );
  QRectF boxRect = QRectF( scaledRect.left(), scaledRect.bottom() - ( s.height() + 2 * margin ), s.width() + 2 * margin, s.height() + 2 * margin );

  QPainterPath p;
  p.moveTo( boxRect.bottomRight() );
  p.lineTo( boxRect.right(), boxRect.top() + margin );
  p.arcTo( boxRect.right() - 2 * margin, boxRect.top(), 2 * margin, 2 * margin, 0, 90 );
  p.lineTo( boxRect.left() + margin, boxRect.top() );
  p.arcTo( boxRect.left(), boxRect.top(), 2 * margin, 2 * margin, 90, 90 );
  p.lineTo( boxRect.bottomLeft() );
  p.lineTo( boxRect.bottomRight() );

  painter->setPen( QColor( 150, 150, 150, 150 ) );
  QLinearGradient g( 0, boxRect.top(), 0, boxRect.bottom() );
  g.setColorAt( 0, QColor( 200, 200, 200, 150 ) );
  g.setColorAt( 1, QColor( 150, 150, 150, 150 ) );

  painter->setBrush( QBrush( g ) );
  painter->drawPath( p );

  painter->setPen( QPen( QColor( 0, 0, 0, 100 ) ) );
  painter->setFont( f );
  painter->drawText( textRect, Qt::AlignBottom, mLabel );
  painter->restore();
}