    /// gives the surface area
    ctype area(int tri) const {
        StaticVector<ctype,3> a = vertices(triangles(tri).vertices[1]) - vertices(triangles(tri).vertices[0]);
        StaticVector<ctype,3> b = vertices(triangles(tri).vertices[2]) - vertices(triangles(tri).vertices[0]);

        return fabs(0.5 * (a.cross(b)).length());
    }