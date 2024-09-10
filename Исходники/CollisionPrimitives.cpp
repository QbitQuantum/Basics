    //-----------------------------------------------------------------------------
    // Frustum Triangle intersection  using separating axis test.
    // note: the frustum and the triangle must be in the same space.
    //       optimization needed
    bool FrustumTriangleIntersect(const Frustum& fr, const Triangle& tri)
    {            
        bool allInside = true;        
        for(int i = 0; i < 6; ++i)
        {
            const Plane& plane = fr[i];
            float d1 = plane.Eval(tri.A);
            float d2 = plane.Eval(tri.B);
            float d3 = plane.Eval(tri.C); 

            // if all outside a single plane, then there is
            // no intersection.
            if( d1 < 0 && d2 < 0 && d3 < 0) 
                return false;
            allInside = allInside && ( d1 > 0 && d2 > 0 && d3 > 0);            
        }

        // the tri is completely inside the frustum.
        if( allInside ) 
            return true; 

        // separating axis test.
        // Triangle:  3 edges  1 face normal.
        // Frustum:   6 edges, 5 face normal.
        // for total of 24 separating axis.
        // note this test can be optimized.
                        
        // tri edges
        float3 triEdges[3];
        triEdges[0] = tri.B - tri.A;
        triEdges[1] = tri.C - tri.A;
        triEdges[2] = tri.C - tri.B;

        // frustum edges
        float3 FrEdges[6];
        FrEdges[0] = fr.Corner(Frustum::NearTopLeft) - fr.Corner(Frustum::NearTopRight);
        FrEdges[1] = fr.Corner(Frustum::NearBottomRight) - fr.Corner(Frustum::NearTopRight);
        FrEdges[2] = (fr.Corner(Frustum::FarBottonLeft) - fr.Corner(Frustum::NearBottonLeft));
        FrEdges[3] = (fr.Corner(Frustum::FarBottomRight) - fr.Corner(Frustum::NearBottomRight));
        FrEdges[4] = (fr.Corner(Frustum::FarTopRight) - fr.Corner(Frustum::NearTopRight));
        FrEdges[5] = (fr.Corner(Frustum::FarTopLeft) - fr.Corner(Frustum::NearTopLeft));

        int k = 0;        
        float3 Axis[24];                
        Axis[k++] = fr.TopPlane().normal;
        Axis[k++] = fr.BottomPlane().normal;
        Axis[k++] = fr.LeftPlane().normal;
        Axis[k++] = fr.RightPlane().normal;
        Axis[k++] = fr.NearPlane().normal;
        Axis[k++] = normalize(cross(triEdges[0], triEdges[1]));

        for(int te = 0;  te < 3; te++)
        {
            for(int fe = 0; fe < 6; fe++)
            {
                float3 axis = cross( triEdges[te], FrEdges[fe]); 
                Axis[k++] = normalize(axis);                
            }
        }
                
        for(int n = 0; n < 24; n++)
        {
            float3 axis = Axis[n];
            if( lengthsquared(axis) < Epsilon) 
                continue;
            float trid1 = dot(tri.A,axis);
            float trid2 = dot(tri.B,axis);
            float trid3 = dot(tri.C,axis);

            float trMin = std::min(trid1,trid2);
            trMin = std::min(trMin, trid3);
            float trMax = std::max(trid1,trid2);
            trMax = std::max(trMax,trid3);

            float frMin = dot(fr.Corner(0),axis);
            float frMax = frMin;
            for(int c = 1; c < 8; c++)
            {
                float fdist = dot(fr.Corner(c), axis);
                frMin = std::min(frMin,fdist);
                frMax = std::max(frMax,fdist);
            }
           
            if( (trMax < frMin) || (frMax < trMin))
            {               
                return false;                
            }
        }

        // must be intersecting.
        return true;
               
    }