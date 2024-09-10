bool
GeoPointList::intersects( const GeoExtent& ex ) const
{
    if ( ex.isInfinite() )
        return true;

    //TODO: srs transform

    if ( ex.isPoint() ) // do a point-in-polygon test
    {
        const GeoPoint& point = ex.getSouthwest();
        bool result = false;
        const GeoPointList& polygon = *this;
        for( unsigned int i=0, j=polygon.size()-1; i<polygon.size(); j = i++ )
        {
            if ((((polygon[i].y() <= point.y()) && (point.y() < polygon[j].y())) ||
                 ((polygon[j].y() <= point.y()) && (point.y() < polygon[i].y()))) &&
                (point.x() < (polygon[j].x()-polygon[i].x()) * (point.y()-polygon[i].y())/(polygon[j].y()-polygon[i].y())+polygon[i].x()))
            {
                result = !result;
            }
        }
        return result;
    }
    else // check for all points within extent -- not actually correct //TODO
    {
        GeoExtent e;
        for( GeoPointList::const_iterator i = begin(); i != end(); i++ )
        {
            if ( i == begin() ) e = GeoExtent( *i, *i );
            else e.expandToInclude( *i );
        }
        return e.intersects( ex );
    }    
}