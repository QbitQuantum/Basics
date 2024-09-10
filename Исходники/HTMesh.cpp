// LINE
void HTMesh::intersect(double ra1, double dec1, double ra2, double dec2,
                       BufNum bufNum)
{
    double x1, y1, z1, x2, y2, z2;
    
    //if (ra1 == 0.0 || ra1 == 180.00) ra1 += 0.1;
    //if (ra2 == 0.0 || ra2 == 180.00) ra2 -= 0.1;
    //if (dec1 == 0.0 ) dec1 += 0.1;
    //if (dec2 == 0.0 ) dec2 -= 0.1;

    // convert to Cartesian. Ugh.
    toXYZ( ra1, dec1, &x1, &y1, &z1);
    toXYZ( ra2, dec2, &x2, &y2, &z2);

    // Check if points are too close
    double len;
    len =  fabs(x1 - x2);
    len += fabs(y1 - y2);
    len += fabs(z1 - z2);

    if (htmDebug > 0 ) {
        printf("htmDebug = %d\n", htmDebug);
        printf("p1 = (%f, %f, %f)\n", x1, y1, z1);
        printf("p2 = (%f, %f, %f)\n", x2, y2, z2);
        printf("edge: %f (radians) %f (degrees)\n", edge, edge / degree2Rad);
        printf("len : %f (radians) %f (degrees)\n", len,  len  / degree2Rad);
    }

    if ( len < edge10 )
        return intersect( ra1, len, bufNum);

    // Cartesian cross product => perpendicular!.  Ugh.
    double cx = y1 * z2 - z1 * y2;
    double cy = z1 * x2 - x1 * z2;
    double cz = x1 * y2 - y1 * x2;

    if ( htmDebug > 0 ) printf("cp  = (%f, %f, %f)\n", cx, cy, cz);

    double norm =  edge10 / ( fabs(cx) + fabs(cy) + fabs(cz) );

    // give it length edge/10
    cx *= norm;
    cy *= norm;
    cz *= norm;

    if ( htmDebug > 0 ) printf("cpn  = (%f, %f, %f)\n", cx, cy, cz);

    // add it to (ra1, dec1)
    cx += x1;
    cy += y1;
    cz += z1;

    if ( htmDebug > 0 ) printf("cpf  = (%f, %f, %f)\n", cx, cy, cz);

    // back to spherical
    norm = sqrt( cx*cx + cy*cy + cz*cz);
    double ra0 = atan2( cy, cx )     / degree2Rad;
    double dec0 = asin( cz / norm )  / degree2Rad;

    if ( htmDebug > 0 ) printf("new ra, dec = (%f, %f)\n", ra0, dec0);

    SpatialVector p1(ra1, dec1);
    SpatialVector p0(ra0, dec0);
    SpatialVector p2(ra2, dec2);
    RangeConvex convex(&p1, &p0, &p2);

    if ( ! performIntersection(&convex, bufNum) )
        printf("In intersect(%f, %f, %f, %f)\n", ra1, dec1, ra2, dec2);
}