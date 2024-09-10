bool
MapInfo::toMapPoint( const GeoPoint& input, GeoPoint& output ) const
{
    return input.isValid() ? input.transform(_profile->getSRS(), output) : false;
}