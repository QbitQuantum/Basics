void CanvasKugarTemplate::draw( QPainter &painter ) {
	painter.setPen( QColor( 0, 0, 0 ) );
	QPoint p1( ( int ) ( x() + props[ "LeftMargin" ].first.toInt() ),
	           ( int ) ( y() + props[ "TopMargin" ].first.toInt() ) );
	QPoint p2( ( int ) ( x() + props[ "LeftMargin" ].first.toInt() ),
	           ( int ) y() + height() - props[ "BottomMargin" ].first.toInt() );
	QPoint p3( ( int ) x() + width() - props[ "RightMargin" ].first.toInt(),
	           ( int ) y() + height() - props[ "BottomMargin" ].first.toInt() );
	QPoint p4( ( int ) x() + width() - props[ "RightMargin" ].first.toInt(),
	           ( int ) ( y() + props[ "TopMargin" ].first.toInt() ) );
	painter.moveTo( p1 );
	painter.lineTo( p2 );
	painter.lineTo( p3 );
	painter.lineTo( p4 );
	painter.lineTo( p1 );
	/*    painter.drawRect((int)(x()+props["LeftMargin"].first.toInt()),
			     (int)(y()+props["TopMargin"].first.toInt()),
			     width() - props["LeftMargin"].first.toInt() - props["RightMargin"].first.toInt(),
			     height() - props["TopMargin"].first.toInt() - props["BottomMargin"].first.toInt());*/
	CanvasSection::draw( painter );
}