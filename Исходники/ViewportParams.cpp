void ViewportParams::centerOn( qreal lon, qreal lat )
{
    if ( !d->m_currentProjection->traversablePoles() ) {
        if ( lat > d->m_currentProjection->maxLat() )
            lat = d->m_currentProjection->maxLat();

        if ( lat < d->m_currentProjection->minLat() )
            lat = d->m_currentProjection->minLat();
    } else {
        while ( lat > M_PI )
            lat -= 2 * M_PI;
        while ( lat < -M_PI )
            lat += 2 * M_PI;
    }

    while ( lon > M_PI )
        lon -= 2 * M_PI;
    while ( lon < -M_PI )
        lon += 2 * M_PI;

    d->m_centerLongitude = lon;
    d->m_centerLatitude = lat;

    Quaternion axis = Quaternion::fromEuler( -lat, lon, 0.0 );
    axis.normalize();

    d->setPlanetAxis( axis );
}