void OsmDatabase::unique( QVector<OsmPlacemark> &placemarks ) const
{
    for ( int i=1; i<placemarks.size(); ++i ) {
        if ( placemarks[i-1] == placemarks[i] ) {
            placemarks.remove( i );
            --i;
        }
    }
}