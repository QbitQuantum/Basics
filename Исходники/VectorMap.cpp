void VectorMap::mercatorCreateFromPntMap( const PntMap* pntmap,
                                          const ViewportParams* viewport )
{
    m_polygons.clear();
    int  radius = viewport->radius();

    // Calculate translation of center point
    const qreal centerLon = viewport->centerLongitude();
    const qreal centerLat = viewport->centerLatitude();

    const qreal rad2Pixel = (float)( 2 * radius ) / M_PI;

    GeoPolygon::PtrVector::ConstIterator  itPolyLine = pntmap->constBegin();
    GeoPolygon::PtrVector::ConstIterator  itEndPolyLine = pntmap->constEnd();

    const QRectF visibleArea ( 0, 0, viewport->width(), viewport->height() );
    const int      detail = getDetailLevel( radius );

    for (; itPolyLine != itEndPolyLine; ++itPolyLine )
    {
        const GeoDataCoordinates::PtrVector boundary = (*itPolyLine)->getBoundary();

        // Let's just use the top left and the bottom right bounding box point for 
        // this projection

        // rather paint an invalid line then crashing here if the boundaries are not loaded yet
        if ( boundary.size() < 3 )
            continue;

        ScreenPolygon  boundingPolygon;

        for ( int i = 1; i < 3; ++i ) {
            qreal lon, lat;
            boundary[i]->geoCoordinates(lon, lat);
            const qreal x = (qreal)(viewport->width())  / 2.0 + rad2Pixel * (lon - centerLon);
            const qreal y = (qreal)(viewport->height()) / 2.0 - rad2Pixel * ( atanh( sin( lat ) )
                                                                            - atanh( sin( centerLat ) ) );

            boundingPolygon << QPointF( x, y );
        }

        // This sorts out polygons by bounding box which aren't visible at all.
        int offset = 0;

        if ( boundingPolygon.at(0).x() < 0 || boundingPolygon.at(1).x() < 0 ) {
            boundingPolygon.translate( 4 * radius, 0 );
            offset += 4 * radius;
        }

        do {
            offset -= 4 * radius;
            boundingPolygon.translate( -4 * radius, 0 );
	    // FIXME: Get rid of this really fugly code once we have a
	    //        proper LatLonBox check implemented and in place.
        } while( ( (*itPolyLine)->getDateLine() != GeoPolygon::Even 
		   && visibleArea.intersects( (QRectF)( boundingPolygon.boundingRect() ) ) )
		 || ( (*itPolyLine)->getDateLine() == GeoPolygon::Even
		      && ( visibleArea.intersects( QRectF( boundingPolygon.at(1),
                                                           QPointF( (qreal)(viewport->width()) / 2.0
                                                                    - rad2Pixel * ( centerLon
                                                                                    - M_PI )
                                                                    + offset,
                                                                    boundingPolygon.at(0).y() ) ) )
                           || visibleArea.intersects( QRectF( QPointF( (qreal)(viewport->width()) / 2.0
                                                                       - rad2Pixel * ( centerLon
                                                                                       + M_PI )
                                                                       + offset,
                                                                       boundingPolygon.at(1).y() ),
                                                              boundingPolygon.at(0) ) ) ) ) );
        offset += 4 * radius;
        boundingPolygon.translate( 4 * radius, 0 );

	// FIXME: Get rid of this really fugly code once we will have
	//        a proper LatLonBox check implemented and in place.
        while ( ( (*itPolyLine)->getDateLine() != GeoPolygon::Even 
		  && visibleArea.intersects( (QRectF)( boundingPolygon.boundingRect() ) ) )
		|| ( (*itPolyLine)->getDateLine() == GeoPolygon::Even 
		     && ( visibleArea.intersects(
			    QRectF( boundingPolygon.at(1),
				    QPointF( (qreal)(viewport->width()) / 2.0
					     - rad2Pixel * ( centerLon - M_PI )
                                             + offset,
					     boundingPolygon.at(0).y() ) ) ) 
			  || visibleArea.intersects(
			         QRectF( QPointF( (qreal)(viewport->width()) / 2.0
						  - rad2Pixel * ( centerLon + M_PI )
                                                  + offset,
						  boundingPolygon.at(1).y() ),
					 boundingPolygon.at(0) ) ) ) )
		)
        {
            mercatorCreatePolyLine( *itPolyLine, detail, viewport, offset );

            offset += 4 * radius;
            boundingPolygon.translate( 4 * radius, 0 );
        }
    }
}