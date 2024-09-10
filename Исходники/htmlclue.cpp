void HTMLCell::select( KHTMLWidget *_htmlw, HTMLChain *_chain, QRect & _rect, int _tx, int _ty )
{
    HTMLObject *obj;

    QRect r( x + _tx, y - ascent + _ty, width, ascent + descent );

    _tx += x;
    _ty += y - ascent;

    bool sel = false;

    if ( _rect.contains( r ) )
    {
	sel = true;
    }
    else if ( !_rect.intersects( r ) )
    {
	sel = false;
    }
    else
    {
	QRect isect = _rect.intersect( r );
	if ( isect.width() > r.width()/2 && isect.height() > r.height()/2 )
	    sel = true;
    }

    _chain->push( this );

    for ( obj = head; obj != 0; obj = obj->next() )
	obj->select( _htmlw, _chain, sel, _tx, _ty );

    _chain->pop();
}