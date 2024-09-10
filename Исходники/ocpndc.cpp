// Draws thick lines from triangles
void DrawGLThickLines( int n, wxPoint points[],wxCoord xoffset,
                       wxCoord yoffset, wxPen pen, bool b_hiqual )
{
#ifdef ocpnUSE_GL
    if(n < 2)
        return;

    /* for dashed case, for now just draw thick lines */
    wxDash *dashes;
    if( pen.GetDashes( &dashes ) )
    {
        wxPoint p0 = points[0];
        for( int i = 1; i < n; i++ ) {
            DrawGLThickLine( p0.x + xoffset, p0.y + yoffset, points[i].x + xoffset,
                             points[i].y + yoffset, pen, b_hiqual );
            p0 = points[i];
        }
        return;
    }

    /* cull zero segments */
    wxPoint *cpoints = new wxPoint[n];
    cpoints[0] = points[0];
    int c = 1;
    for( int i = 1; i < n; i++ ) {
        if(points[i].x != points[i-1].x || points[i].y != points[i-1].y)
            cpoints[c++] = points[i];
    }

    /* nicer than than rendering each segment separately, this is because thick
       line segments drawn as rectangles which have different angles have
       rectangles which overlap and also leave a gap.
       This code properly calculates vertexes for adjoining segments */
    float t1 = pen.GetWidth();

    float x0 = cpoints[0].x, y0 = cpoints[0].y, x1 = cpoints[1].x, y1 = cpoints[1].y;
    float a0 = atan2f( y1 - y0, x1 - x0 );

    // It is also possible to use triangle strip, (and triangle fan for endcap)
    // to reduce vertex count.. is it worth it?
    glBegin( GL_TRIANGLES );

    float t2sina0 = t1 / 2 * sinf( a0 );
    float t2cosa0 = t1 / 2 * cosf( a0 );

    for( int i = 1; i < c; i++ ) {
        float x2, y2;
        float a1;

        if(i < c - 1) {
            x2 = cpoints[i + 1].x, y2 = cpoints[i + 1].y;
            a1 = atan2f( y2 - y1, x2 - x1 );
        } else {
            x2 = x1, y2 = y1;
            a1 = a0;
        }

        float aa = (a0 + a1) / 2;
        float diff = fabsf(a0 - a1);
        if(diff > M_PI)
            diff -= 2 * (float)M_PI;
        float rad = t1 / 2 / wxMax(cosf(diff / 2), .4);

        float t2sina1 = rad * sinf( aa );
        float t2cosa1 = rad * cosf( aa );

        glVertex2f( x1 + t2sina1, y1 - t2cosa1 );
        glVertex2f( x1 - t2sina1, y1 + t2cosa1 );
        glVertex2f( x0 + t2sina0, y0 - t2cosa0 );

        glVertex2f( x0 - t2sina0, y0 + t2cosa0 );
        glVertex2f( x0 + t2sina0, y0 - t2cosa0 );

        float dot = t2sina0 * t2sina1 + t2cosa0 * t2cosa1;
        if(dot > 0)
            glVertex2f( x1 - t2sina1, y1 + t2cosa1 );
        else
            glVertex2f( x1 + t2sina1, y1 - t2cosa1 );

        x0 = x1, x1 = x2;
        y0 = y1, y1 = y2;
        a0 = a1;
        t2sina0 = t2sina1, t2cosa0 = t2cosa1;
    }
 
    if(pen.GetCap() == wxCAP_ROUND) {
        DrawEndCap( x0, y0, t1, a0);
        DrawEndCap( x0, y0, t1, a0 + M_PI);
     }

    glEnd();

    glPopAttrib();

    delete [] cpoints;

 #endif    
 }