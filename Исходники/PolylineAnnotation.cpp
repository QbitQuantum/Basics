void PolylineAnnotation::move( const GeoDataCoordinates &source, const GeoDataCoordinates &destination )
{
    GeoDataLineString *lineString = static_cast<GeoDataLineString*>( placemark()->geometry() );
    GeoDataLineString oldLineString = *lineString;
    lineString->clear();

    const qreal deltaLat = destination.latitude() - source.latitude();
    const qreal deltaLon = destination.longitude() - source.longitude();

    Quaternion latRectAxis = Quaternion::fromEuler( 0, destination.longitude(), 0);
    Quaternion latAxis = Quaternion::fromEuler( -deltaLat, 0, 0);
    Quaternion lonAxis = Quaternion::fromEuler(0, deltaLon, 0);
    Quaternion rotAxis = latRectAxis * latAxis * latRectAxis.inverse() * lonAxis;

    qreal lonRotated, latRotated;
    for ( int i = 0; i < oldLineString.size(); ++i ) {
        Quaternion qpos = oldLineString.at(i).quaternion();
        qpos.rotateAroundAxis(rotAxis);
        qpos.getSpherical( lonRotated, latRotated );
        GeoDataCoordinates movedPoint( lonRotated, latRotated, 0 );

        lineString->append( movedPoint );
    }
}