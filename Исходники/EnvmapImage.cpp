Rgba
EnvmapImage::filteredLookup (V3f d, float r, int n) const
{
    //
    // Filtered environment map lookup: Take n by n point samples
    // from the environment map, clustered around direction d, and
    // combine the samples with a tent filter.
    //
    
    //
    // Depending on the type of map, pick an appropriate function
    // to convert 3D directions to 2D pixel poitions.
    //

    V2f (* dirToPos) (const Box2i &, const V3f &);

    if (_type == ENVMAP_LATLONG)
	dirToPos = dirToPosLatLong;
    else
	dirToPos = dirToPosCube;

    //
    // Pick two vectors, dx and dy, of length r, that are orthogonal
    // to the lookup direction, d, and to each other.
    //

    d.normalize();
    V3f dx, dy;

    if (abs (d.x) > 0.707f)
	dx = (d % V3f (0, 1, 0)).normalized() * r;
    else
	dx = (d % V3f (1, 0, 0)).normalized() * r;

    dy = (d % dx).normalized() * r;

    //
    // Take n by n point samples from the map, and add them up.
    // The directions for the point samples are all within the pyramid
    // defined by the vectors d-dy-dx, d-dy+dx, d+dy-dx, d+dy+dx.
    //

    float wt = 0;

    float cr = 0;
    float cg = 0;
    float cb = 0;
    float ca = 0;

    for (int y = 0; y < n; ++y)
    {
	float ry = float (2 * y + 2) / float (n + 1) - 1;
	float wy = 1 - abs (ry);
	V3f ddy (ry * dy);

	for (int x = 0; x < n; ++x)
	{
	    float rx = float (2 * x + 2) / float (n + 1) - 1;
	    float wx = 1 - abs (rx);
	    V3f ddx (rx * dx);
	    
	    Rgba s = sample (dirToPos (_dataWindow, d + ddx + ddy));

	    float w = wx * wy;
	    wt += w;

	    cr += s.r * w;
	    cg += s.g * w;
	    cb += s.b * w;
	    ca += s.a * w;
	}
    }

    wt = 1 / wt;

    Rgba c;

    c.r = cr * wt;
    c.g = cg * wt;
    c.b = cb * wt;
    c.a = ca * wt;

    return c;
}