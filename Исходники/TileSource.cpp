bool
TileSource::hasDataInExtent( const GeoExtent& extent ) const
{
    //If no data extents are provided, just return true
    if ( _dataExtents.size() == 0 )
        return true;

    bool intersects = false;

    for (DataExtentList::const_iterator itr = _dataExtents.begin(); itr != _dataExtents.end(); ++itr)
    {
        if ( extent.intersects( *itr ) )
        {
            intersects = true;
            break;
        }
    }
    return intersects;
}