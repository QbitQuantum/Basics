//----------------------------------------------------------------------------
void ConvexPolyhedron::Create (const vector<Vector3>& rakPoint,
                               const vector<int>& raiConnect)
{
    assert( rakPoint.size() >= 4 && raiConnect.size() >= 4 );

    int iVQuantity = rakPoint.size();
    int iTQuantity = raiConnect.size()/3;
    int iEQuantity = iVQuantity + iTQuantity - 2;
    Reset(iVQuantity,iEQuantity,iTQuantity);
    m_akPoint = rakPoint;

    // Copy polyhedron points into vertex array.  Compute centroid for use in
    // making sure the triangles are counterclockwise oriented when viewed
    // from the outside.
    ComputeCentroid();

    // get polyhedron edge and triangle information
    for (int iT = 0, iIndex = 0; iT < iTQuantity; iT++)
    {
        // get vertex indices for triangle
        int iV0 = raiConnect[iIndex++];
        int iV1 = raiConnect[iIndex++];
        int iV2 = raiConnect[iIndex++];

        // make sure triangle is counterclockwise
        Vector3& rkV0 = m_akPoint[iV0];
        Vector3& rkV1 = m_akPoint[iV1];
        Vector3& rkV2 = m_akPoint[iV2];

        Vector3 kDiff = m_kCentroid - rkV0;
        Vector3 kE1 = rkV1 - rkV0;
        Vector3 kE2 = rkV2 - rkV0;
        Vector3 kNormal = kE1.Cross(kE2);
        Real fLength = kNormal.Length();
        if ( fLength > 1e-06f )
        {
            kNormal /= fLength;
        }
        else
        {
            kNormal = kDiff;
            kNormal.Unitize();
        }

        Real fDistance = kNormal.Dot(kDiff);

        if ( fDistance < 0.0f )
        {
            // triangle is counterclockwise
            Insert(iV0,iV1,iV2);
        }
        else
        {
            // triangle is clockwise
            Insert(iV0,iV2,iV1);
        }
    }

    UpdatePlanes();
}