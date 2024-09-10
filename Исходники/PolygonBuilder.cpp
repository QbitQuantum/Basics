// Initialize polypartition TPPLPoly from a list of indices and vertices
//
// verts     - 3D polygon vertex vectors
// xind,yind - Indices of 3D vectors to extract as x and y coordinates for 2D
//             triangulation computation.
// inds,size - Array of indices into the `verts` list
// isHole    - Value for the hole flag, and to determine the orientation
static void initTPPLPoly(TPPLPoly& poly,
                         const std::vector<float>& verts,
                         int xind, int yind,
                         const GLuint* inds, int size,
                         bool isHole)
{
    // Check for explicitly closed polygons (last and first vertices equal) and
    // discard the last vertex in these cases.  This is a pretty stupid
    // convention, but the OGC have blessed it and now we've got a bunch of
    // geospatial formats (kml, WKT, GeoJSON) which require it.  Sigh.
    // http://gis.stackexchange.com/questions/10308/why-do-valid-polygons-repeat-the-same-start-and-end-point/10309#10309
    if (inds[0] == inds[size-1] ||
        (verts[3*inds[0]+0] == verts[3*inds[size-1]+0] &&
         verts[3*inds[0]+1] == verts[3*inds[size-1]+1] &&
         verts[3*inds[0]+2] == verts[3*inds[size-1]+2]))
    {
        g_logger.warning_limited("Ignoring duplicate final vertex in explicitly closed polygon");
        size -= 1;
    }
    // Copy into polypartition data structure
    poly.Init(size);
    for (int i = 0; i < size; ++i)
    {
        poly[i].x = verts[3*inds[i]+xind];
        poly[i].y = verts[3*inds[i]+yind];
        poly[i].id = inds[i];
    }
    int orientation = poly.GetOrientation();
    // Invert so that outer = ccw, holes = cw
    if ((orientation == TPPL_CW) ^ isHole)
        poly.Invert();
    poly.SetHole(isHole);
}