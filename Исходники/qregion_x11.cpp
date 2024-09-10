QRegion::QRegion( const QRect &r, RegionType t )
{
    QRect rr = r.normalize();
    data = new QRegionData;
    CHECK_PTR( data );
    data->is_null = FALSE;
    if ( t == Rectangle ) {			// rectangular region
	data->rgn = XCreateRegion();
	XRectangle xr;
	xr.x = rr.x();
	xr.y = rr.y();
	xr.width  = rr.width();
	xr.height = rr.height();
	XUnionRectWithRegion( &xr, data->rgn, data->rgn );
    } else if ( t == Ellipse ) {		// elliptic region
	QPointArray a;
	a.makeEllipse( rr.x(), rr.y(), rr.width(), rr.height() );
	data->rgn = XPolygonRegion( (XPoint*)a.data(), a.size(), EvenOddRule );
    }
}