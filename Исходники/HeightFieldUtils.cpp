void
HeightFieldUtils::resolveInvalidHeights(osg::HeightField* grid,
                                        const GeoExtent&  ex,
                                        float             invalidValue,
                                        const Geoid*      geoid)
{
    if ( geoid )
    {
        // need the lat/long extent for geoid queries:
        unsigned numRows = grid->getNumRows();
        unsigned numCols = grid->getNumColumns();
        GeoExtent geodeticExtent = ex.getSRS()->isGeographic() ? ex : ex.transform( ex.getSRS()->getGeographicSRS() );
        double latMin = geodeticExtent.yMin();
        double lonMin = geodeticExtent.xMin();
        double lonInterval = geodeticExtent.width() / (double)(numCols-1);
        double latInterval = geodeticExtent.height() / (double)(numRows-1);

        for( unsigned r=0; r<numRows; ++r )
        {
            double lat = latMin + latInterval*(double)r;
            for( unsigned c=0; c<numCols; ++c )
            {
                double lon = lonMin + lonInterval*(double)c;
                if ( grid->getHeight(c, r) == invalidValue )
                {
                    grid->setHeight( c, r, geoid->getHeight(lat, lon) );
                }
            }
        }
    }
    else
    {
        for(unsigned int i=0; i<grid->getHeightList().size(); i++ )
        {
            if ( grid->getHeightList()[i] == invalidValue )
            {
                grid->getHeightList()[i] = 0.0;
            }
        }
    }
}