void SHAPE_POLY_SET::fractureSingle( POLYGON& paths )
{
    FractureEdgeSet edges;
    FractureEdgeSet border_edges;
    FractureEdge* root = NULL;

    bool first = true;

    if( paths.size() == 1 )
        return;

    int num_unconnected = 0;

    for( SHAPE_LINE_CHAIN& path : paths )
    {
        int index = 0;

        FractureEdge *prev = NULL, *first_edge = NULL;

        int x_min = std::numeric_limits<int>::max();

        for( int i = 0; i < path.PointCount(); i++ )
        {
            const VECTOR2I& p = path.CPoint( i );

            if( p.x < x_min )
                x_min = p.x;
        }

        for( int i = 0; i < path.PointCount(); i++ )
        {
            FractureEdge* fe = new FractureEdge( first, &path, index++ );

            if( !root )
                root = fe;

            if( !first_edge )
                first_edge = fe;

            if( prev )
                prev->m_next = fe;

            if( i == path.PointCount() - 1 )
                fe->m_next = first_edge;

            prev = fe;
            edges.push_back( fe );

            if( !first )
            {
                if( fe->m_p1.x == x_min )
                    border_edges.push_back( fe );
            }

            if( !fe->m_connected )
                num_unconnected++;
        }
        first = false; // first path is always the outline
    }

    // keep connecting holes to the main outline, until there's no holes left...
    while( num_unconnected > 0 )
    {
        int x_min = std::numeric_limits<int>::max();

        FractureEdge* smallestX = NULL;

        // find the left-most hole edge and merge with the outline
        for( FractureEdgeSet::iterator i = border_edges.begin(); i != border_edges.end(); ++i )
        {
            int xt = (*i)->m_p1.x;

            if( ( xt < x_min ) && ! (*i)->m_connected )
            {
                x_min = xt;
                smallestX = *i;
            }
        }

        num_unconnected -= processEdge( edges, smallestX );
    }

    paths.clear();
    SHAPE_LINE_CHAIN newPath;

    newPath.SetClosed( true );

    FractureEdge* e;

    for( e = root; e->m_next != root; e = e->m_next )
        newPath.Append( e->m_p1 );

    newPath.Append( e->m_p1 );

    for( FractureEdgeSet::iterator i = edges.begin(); i != edges.end(); ++i )
        delete *i;

    paths.push_back( newPath );
}