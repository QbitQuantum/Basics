//----------------------------------------------------------------------------
bool Portal::ReducedFrustum (const Culler& culler,
                             float reducedFrustum[6])
{
    // The portal polygon is transformed into the camera coordinate system
    // and projected onto the near plane.  An axis-aligned bounding rectangle
    // is computed for the projected points and clipped against the left,
    // right, bottom, and top frustum planes.  The result is itself an
    // axis-aligned bounding rectangle that is used to define a "reduced
    // frustum" to be used for drawing what is visible through the portal
    // polygon.
    //
    // The algorithm must handle the situation when portal polygon vertices
    // are behind the observer.  Imagine standing in a room with a doorway
    // immediately to your left.  Part of the doorway frame is in front of
    // you (and visible) and part of it is behind you (and not visible).
    // A portal point is represented by P = E + d*D + u*U + r*R, where E is
    // the world location for the eye point, D is the camera's world direction
    // vector, U is the camera's world up vector, and R is the camera's world
    // right vector.  The camera coordinates for the portal point are (d,u,r).
    // If d > 0, P is in front of the eye point and has a projection onto the
    // near plane d = n.  If d < 0, P is behind the eye point and does not
    // have a projection onto the near plane.  If d = 0, P projects to
    // "infinity" on the near plane, a problematic case to deal with.
    //
    // To avoid dealing with d = 0, choose a small value e such that
    // 0 < e < n.  The portal polygon is clipped against the plane d = e,
    // keeping only that portion whose points satisfy d >= e.  The clipped
    // polygon always has a projection onto the near plane.  The axis-aligned
    // bounding box for this projection is computed; clipped against the
    // left, right, bottom, and top of the frustum; and the result used to
    // define the reduced frustum.  All this is designed for an inexact
    // culling of the objects in the adjacent room, so it is useful to avoid
    // preserving the topology of the portal polygon as it is clipped.
    // Instead, the portal polygon vertices with d > e are projected and
    // the intersection points of portal polygon edges with d = e are
    // computed and projected.  The axis-aligned bounding box is computed for
    // the projections, a process that does not require knowing the polygon
    // topology.  The algorithm is essentially the one used for clipping a
    // convex polygon against the view frustum in the software renderer.  The
    // polygon vertices are traversed in-order and the signs of the d values
    // are updated accordingly.  This avoids computing d-signs twice per
    // vertex.

    const Camera* camera = culler.GetCamera();
    const float* frustum = culler.GetFrustum();
    float rmin = +Mathf::MAX_REAL;  // left
    float rmax = -Mathf::MAX_REAL;  // right
    float umin = +Mathf::MAX_REAL;  // bottom
    float umax = -Mathf::MAX_REAL;  // top

    AVector diff;
    APoint vertexCam;
    int i;

    if (camera->IsPerspective())
    {
        const float epsilon = 1e-6f, invEpsilon = 1e+6f;
        int firstSign = 0, lastSign = 0;  // in {-1,0,1}
        bool signChange = false;
        APoint firstVertex = APoint::ORIGIN;
        APoint lastVertex = APoint::ORIGIN;
        float NdD, UdD, RdD, t;

        for (i = 0; i < mNumVertices; i++)
        {
            diff = mWorldVertices[i] - camera->GetPosition();
            vertexCam[0] = diff.Dot(camera->GetDVector());
            vertexCam[1] = diff.Dot(camera->GetUVector());
            vertexCam[2] = diff.Dot(camera->GetRVector());
            vertexCam[3] = 1.0f;

            if (vertexCam[0] > epsilon)
            {
                if (firstSign == 0)
                {
                    firstSign = 1;
                    firstVertex = vertexCam;
                }

                NdD = frustum[Camera::VF_DMIN]/vertexCam[0];
                UdD = vertexCam[1]*NdD;
                RdD = vertexCam[2]*NdD;

                if (UdD < umin)
                {
                    umin = UdD;
                }
                if (UdD > umax)
                {
                    umax = UdD;
                }

                if (RdD < rmin)
                {
                    rmin = RdD;
                }
                if (RdD > rmax)
                {
                    rmax = RdD;
                }

                if (lastSign < 0)
                {
                    signChange = true;
                }

                lastSign = 1;
            }
            else
            {
                if (firstSign == 0)
                {
                    firstSign = -1;
                    firstVertex = vertexCam;
                }

                if (lastSign > 0)
                {
                    signChange = true;
                }

                lastSign = -1;
            }

            if (signChange)
            {
                diff = vertexCam - lastVertex;
                t = (epsilon - lastVertex[0])/diff[0];
                NdD = frustum[Camera::VF_DMIN]*invEpsilon;
                UdD = (lastVertex[1] + t*diff[1])*NdD;
                RdD = (lastVertex[2] + t*diff[2])*NdD;

                if (UdD < umin)
                {
                    umin = UdD;
                }
                if (UdD > umax)
                {
                    umax = UdD;
                }

                if (RdD < rmin)
                {
                    rmin = RdD;
                }
                if (RdD > rmax)
                {
                    rmax = RdD;
                }

                signChange = false;
            }

            lastVertex = vertexCam;
        }

        if (firstSign*lastSign < 0)
        {
            // Process the last polygon edge.
            diff = firstVertex - lastVertex;
            t = (epsilon - lastVertex[0])/diff[0];
            UdD = (lastVertex[1] + t*diff[1])*invEpsilon;
            RdD = (lastVertex[2] + t*diff[2])*invEpsilon;

            if (UdD < umin)
            {
                umin = UdD;
            }
            if (UdD > umax)
            {
                umax = UdD;
            }

            if (RdD < rmin)
            {
                rmin = RdD;
            }
            if (RdD > rmax)
            {
                rmax = RdD;
            }
        }
    }
    else
    {
        for (i = 0; i < mNumVertices; i++)
        {
            diff = mWorldVertices[i] - camera->GetPosition();
            vertexCam[1] = diff.Dot(camera->GetUVector());
            vertexCam[2] = diff.Dot(camera->GetRVector());

            if (vertexCam[1] < umin)
            {
                umin = vertexCam[1];
            }
            if (vertexCam[1] > umax)
            {
                umax = vertexCam[1];
            }

            if (vertexCam[2] < rmin)
            {
                rmin = vertexCam[2];
            }
            if (vertexCam[2] > rmax)
            {
                rmax = vertexCam[2];
            }
        }
    }

    // Test whether the axis-aligned bounding rectangle is outside the current
    // frustum.  If it is, the adjoining room need not be visited.
    if (frustum[Camera::VF_RMIN] >= rmax ||
            frustum[Camera::VF_RMAX] <= rmin ||
            frustum[Camera::VF_UMIN] >= umax ||
            frustum[Camera::VF_UMAX] <= umin)
    {
        return false;
    }

    // The axis-aligned bounding rectangle intersects the current frustum.
    // Reduce the frustum for use in drawing the adjoining room.
    for (int j = 0; j < 6; ++j)
    {
        reducedFrustum[j] = frustum[j];
    }

    if (reducedFrustum[Camera::VF_RMIN] < rmin)
    {
        reducedFrustum[Camera::VF_RMIN] = rmin;
    }

    if (reducedFrustum[Camera::VF_RMAX] > rmax)
    {
        reducedFrustum[Camera::VF_RMAX] = rmax;
    }

    if (reducedFrustum[Camera::VF_UMIN] < umin)
    {
        reducedFrustum[Camera::VF_UMIN] = umin;
    }

    if (reducedFrustum[Camera::VF_UMAX] > umax)
    {
        reducedFrustum[Camera::VF_UMAX] = umax;
    }

    return true;
}