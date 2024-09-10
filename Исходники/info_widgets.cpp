void VLCStatsView::addHistoryValue( float value )
{
    /* We keep a full history by creating virtual blocks for inserts, growing
       by power of 2 when no more space is available. At this time, we also
       free space by agregating the oldest values 2 by 2.
       Each shown value finally being a mean of blocksize samples.
    */
    bool doinsert = false;
    int next_blocksize = blocksize;
    QPolygonF shape = historyShape->polygon();
    int count = shape.count();
    if ( count == 0 )
    {
        shape << QPointF( 0, 0 ); /* begin and close shape */
        shape << QPointF( count, 0 );
    }

    valuesaccumulator += ( value / blocksize );
    valuesaccumulatorcount++;

    if ( valuesaccumulatorcount == blocksize )
    {
        valuesaccumulator = 0;
        valuesaccumulatorcount = 0;
        doinsert = true;
    }

    if ( doinsert )
    {
        if ( count > ( STATS_LENGTH + 2 ) )
        {
            float y = 0;
            y += ((QPointF &) shape.at( historymergepointer + 1 )).y();
            y += ((QPointF &) shape.at( historymergepointer + 2 )).y();
            y /= 2;

            /* merge */
            shape.remove( historymergepointer + 2 );
            ( (QPointF &) shape.at( historymergepointer + 1 ) ).setY( y );
            for(int i=historymergepointer +1; i<( STATS_LENGTH + 2 ); i++)
                ( (QPointF &) shape.at(i) ).setX( i - 1 ); /*move back values*/
            historymergepointer++;
            if ( historymergepointer > ( STATS_LENGTH - 1 ) )
            {
                historymergepointer = 0;
                next_blocksize = ( blocksize << 1 );
            }
        }

        shape.insert( shape.end() - 1, QPointF( count, value ) );
        ( (QPointF &) shape.last() ).setX( count );
    }
    else
        ( (QPointF &) shape.last() ).setX( count - 1 );

    historyShape->setPolygon( shape );

    blocksize = next_blocksize;
}