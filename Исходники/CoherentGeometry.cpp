    bool CCoherentGeometry::IntersectRayTriangle(
        const Vec3& rayOrigin, const Vec3& rayDirection,
        const Vec3& v0, const Vec3& v1, const Vec3& v2,
        float& t, float& u, float& v )
    {
        // Moller-Trumbore ray-triangle intersection
        Vec3 e1 = v1 - v0;
        Vec3 e2 = v2 - v0;

        Vec3 pvec = rayDirection.cross( e2 );

        float det = e1.dot( pvec );

        static const float DET_EPSILON = 0.001f;

        // With culling
        if ( det < DET_EPSILON )
        {
            return false;
        }

        Vec3 tvec = rayOrigin - v0;
        u = tvec.dot( pvec );

        if ( u < 0 || u > det )
        {
            return false;
        }

        Vec3 qvec = tvec.cross( e1 );

        v = rayDirection.dot( qvec );

        if ( v < 0 || u + v > det )
        {
            return false;
        }

        float detRcp = 1.0f / det;
        t = e2.dot( qvec ) * detRcp;
        u *= detRcp;
        v *= detRcp;

        return true;
    }