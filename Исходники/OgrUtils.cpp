Symbology::Polygon*
OgrUtils::createPolygon( OGRGeometryH geomHandle )
{
    Symbology::Polygon* output = 0L;

    int numParts = OGR_G_GetGeometryCount( geomHandle );
    if ( numParts == 0 )
    {
        int numPoints = OGR_G_GetPointCount( geomHandle );
        output = new Symbology::Polygon( numPoints );
        populate( geomHandle, output, numPoints );
        output->open();
    }
    else if ( numParts > 0 )
    {
        for( int p = 0; p < numParts; p++ )
        {
            OGRGeometryH partRef = OGR_G_GetGeometryRef( geomHandle, p );
            int numPoints = OGR_G_GetPointCount( partRef );
            if ( p == 0 )
            {
                output = new Symbology::Polygon( numPoints );
                populate( partRef, output, numPoints );
                //output->open();
                output->rewind( Symbology::Ring::ORIENTATION_CCW );
            }
            else
            {
                Symbology::Ring* hole = new Symbology::Ring( numPoints );
                populate( partRef, hole, numPoints );
                //hole->open();
                hole->rewind( Symbology::Ring::ORIENTATION_CW );
                output->getHoles().push_back( hole );
            }
        }
    }
    return output;
}