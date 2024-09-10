void Frame::getWidgetsInRect( List<Widget*>& l, const Rect r, bool recursive )
{
  l.append( this );
  for( int i = 0; i < numChildren(); i++ ) {
    Widget* o = child( i );
		if ( recursive ) {
			if ( r.intersects( Rect( o->absoluteXPos(), o->absoluteYPos(), o->width(), o->height() ) ) ) {
        o->getWidgetsInRect( l, r );
      }
		} else {
			l.append( o );
		}
	}
}