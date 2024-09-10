static void
simplifyDP( Real tol, std::vector<Wml::Vector3<Real> > & v, int j, int k, std::vector<bool> & mk )
{
    if (k <= j+1) // there is nothing to simplify
        return;

    // check for adequate approximation by segment S from v[j] to v[k]
    int     maxi = j;          // index of vertex farthest from S
    Real   maxd2 = 0;         // distance squared of farthest vertex
    Real   tol2 = tol * tol;  // tolerance squared
	Wml::Segment3<Real> S;    // segment from v[j] to v[k]
		S.Origin = v[j];
		S.Direction = v[k] - v[j];
		S.Extent = S.Direction.Normalize();
	Wml::Vector3<Real> u( S.Direction );  // segment direction vector
	Real cu = u.SquaredLength();            // segment length squared

    // test each vertex v[i] for max distance from S
    // compute using the Feb 2001 Algorithm's dist_Point_to_Segment()
    // Note: this works in any dimension (2D, 3D, ...)
	Wml::Vector3<Real> w;
	Wml::Vector3<Real> Pb;   // base of perpendicular from v[i] to S
	Real b, cw, dv2;         // dv2 = distance v[i] to S squared

    for (int i = j+1; i < k; i++)
    {
        // compute distance squared
		w = v[i] - S.Origin;
        cw = w.Dot(u);
        if ( cw <= 0 )
			dv2 = (v[i] - S.Origin).SquaredLength();
        else if ( cu <= cw )
			dv2 = (v[i] - (S.Origin + S.Direction)).SquaredLength();
        else {
            b = cw / cu;
            Pb = S.Origin + u * b;
			dv2 = (v[i] - Pb).SquaredLength();
        }
        // test with current max distance squared
        if (dv2 <= maxd2)
            continue;
        // v[i] is a new max vertex
        maxi = i;
        maxd2 = dv2;
    }
    if (maxd2 > tol2)        // error is worse than the tolerance
    {
        // split the polyline at the farthest vertex from S
        mk[maxi] = true;      // mark v[maxi] for the simplified polyline
        // recursively simplify the two subpolylines at v[maxi]
        simplifyDP( tol, v, j, maxi, mk );  // polyline v[j] to v[maxi]
        simplifyDP( tol, v, maxi, k, mk );  // polyline v[maxi] to v[k]
    }
    // else the approximation is OK, so ignore intermediate vertices
    return;
}