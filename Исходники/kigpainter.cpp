void KigPainter::drawCurve( const CurveImp* curve )
{
    // we manage our own overlay
    bool tNeedOverlay = mNeedOverlay;
    mNeedOverlay = false;

    QPen pen = mP.pen();

    // this stack contains pairs of Coordinates ( parameter intervals )
    // that we still need to process:
    std::stack<workitem> workstack;
    // mp: this stack contains all the generated overlays:
    // the strategy for generating the overlay structure is the same
    // recursive-like used to draw the segments: a new rectangle is
    // generated whenever the length of a segment becomes lower than
    // overlayRectSize(), or if the segment would be drawn anyway
    // to avoid strange things from happening we impose that the distance
    // in parameter space be less than a threshold before generating
    // any overlay.
    //
    // The third parameter in workitem is a pointer into a stack of
    // all generated rectangles (in real coordinate space); if 0
    // there is no rectangles associated to that segment yet.
    //
    // Using the final mOverlay stack would be much more efficient, but
    // 1. needs transformations into window space
    // 2. would be more difficult to drop rectangles not intersecting
    //    the window.
    std::stack<Rect> overlaystack;

    // mp: the original version in which an initial set of 20 intervals
    // were pushed onto the stack is replaced by a single interval and
    // by forcing subdivision till h < hmax (with more or less the same
    // final result).
    // First push the [0,1] interval into the stack:

    Coordinate coo1 = curve->getPoint( 0., mdoc );
    Coordinate coo2 = curve->getPoint( 1., mdoc );
    workstack.push( workitem(
                        coordparampair( 0., coo1 ),
                        coordparampair( 1., coo2 ),
                        0 ) );

    // maxlength is the square of the maximum size that we allow
    // between two points..
    double maxlength = 1.5 * pixelWidth();
    maxlength *= maxlength;
    // error squared is required to be less that sigma (half pixel)
    double sigma = maxlength/4;
    // distance between two parameter values cannot be too small
    double hmin = 3e-5;
    // distance between two parameter values cannot be too large
    double hmax = 1./40;
    double hmaxoverlay = 1./8;

    int count = 1;               // the number of segments we've already
    // visited...
    static const int maxnumberofpoints = 1000;

    const Rect& sr = window();

    // what this algorithm does is approximating the curve with a set of
    // segments.  we don't draw the individual segments, but use
    // QPainter::drawPolyline() so that the line styles work properly.
    // Possibly there are performance advantages as well ?  this array
    // is a buffer of the polyline approximation of the part of the
    // curve that we are currently processing.
    QPolygon curpolyline( 1000 );
    int curpolylinenextfree = 0;

    // we don't use recursion, but a stack based approach for efficiency
    // concerns...
    while ( ! workstack.empty() && count < maxnumberofpoints )
    {
        workitem curitem = workstack.top();
        workstack.pop();
        bool curitemok = true;
        while ( curitemok && count++ < maxnumberofpoints )
        {
            double t0 = curitem.first.first;
            double t1 = curitem.second.first;
            Coordinate p0 = curitem.first.second;
            bool valid0 = p0.valid();
            Coordinate p1 = curitem.second.second;
            bool valid1 = p1.valid();

            // we take the middle parameter of the two previous points...
            double t2 = ( t0 + t1 ) / 2;
            double h = fabs( t1 - t0 ) /2;

            // if exactly one of the two endpoints is invalid, then
            // we prefer to find an internal value of the parameter
            // separating valid points from invalid points.  We use
            // a bisection strategy (this is not implemented yet!)
//      if ( ( valid0 && ! valid1 ) || ( valid1 && ! valid0 ) )
//      {
//	while ( h >= hmin )
//	{
//	  .......................................
//	}
//      }

            Rect *overlaypt = curitem.overlay;
            Coordinate p2 = curve->getPoint( t2, mdoc );
            bool allvalid = p2.valid() && valid0 && valid1;
            bool dooverlay = ! overlaypt && h < hmaxoverlay && valid0 && valid1
                             && fabs( p0.x - p1.x ) <= overlayRectSize()
                             && fabs( p0.y - p1.y ) <= overlayRectSize();
            bool addn = sr.contains( p2 ) || h >= hmax;
            // estimated error between the curve and the segments
            double errsq = 1e21;
            if ( allvalid ) errsq = (0.5*p0 + 0.5*p1 - p2).squareLength();
            errsq /= 4;
            curitemok = false;
//      bool dodraw = allvalid && h < hmax && ( errsq < sigma || h < hmin );
            bool dodraw = allvalid && h < hmax && errsq < sigma;
            if ( tNeedOverlay && ( dooverlay || dodraw ) )
            {
                Rect newoverlay( p0, p1 );
                overlaystack.push( newoverlay );
                overlaypt = &overlaystack.top();
            }
            if ( overlaypt ) overlaypt->setContains( p2 );
            if ( dodraw )
            {
                // draw the two segments
                QPoint tp0 = toScreen(p0);
                QPoint tp1 = toScreen(p1);
                QPoint tp2 = toScreen(p2);
                if ( curpolylinenextfree > 0 && curpolyline[curpolylinenextfree - 1] != tp1 )
                {
                    // flush the current part of the curve
                    mP.drawPolyline( curpolyline.constData(), curpolylinenextfree );
                    curpolylinenextfree = 0;
                }
                if ( curpolylinenextfree == 0 )
                    curpolyline[curpolylinenextfree++] = tp1;
                curpolyline[curpolylinenextfree++] = tp2;
                curpolyline[curpolylinenextfree++] = tp0;
            }
            else if ( h >= hmin )   // we do not continue to subdivide indefinitely!
            {
                // push into stack in order to process both subintervals
                if ( addn || ( valid0 && sr.contains( p0 ) ) )
                    workstack.push( workitem( curitem.first, coordparampair( t2, p2 ),
                                              overlaypt ) );
                if ( addn || ( valid1 && sr.contains( p1 ) ) )
                {
                    curitem = workitem( coordparampair( t2, p2 ), curitem.second ,
                                        overlaypt );
                    curitemok = true;
                }
            }
        }
    }
    // flush the rest of the curve
    mP.drawPolyline( curpolyline.constData(), curpolylinenextfree );
    curpolylinenextfree = 0;

    if ( ! workstack.empty () )
        qDebug() << "Stack not empty in KigPainter::drawCurve!\n";
    assert ( tNeedOverlay || overlaystack.empty() );
    if ( tNeedOverlay )
    {
        Rect border = window();
        while ( ! overlaystack.empty() )
        {
            Rect overlay = overlaystack.top();
            overlaystack.pop();
            if (overlay.intersects( border ))
                mOverlay.push_back( toScreenEnlarge( overlay ) );
        }
    }
    mNeedOverlay = tNeedOverlay;
}