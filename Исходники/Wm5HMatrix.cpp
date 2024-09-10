//----------------------------------------------------------------------------
void HMatrix::MakeObliqueProjection (const APoint& origin,
    const AVector& normal, const AVector& direction)
{
    // The projection plane is Dot(N,X-P) = 0 where N is a 3-by-1 unit-length
    // normal vector and P is a 3-by-1 point on the plane.  The projection
    // is oblique to the plane, in the direction of the 3-by-1 vector D.
    // Necessarily Dot(N,D) is not zero for this projection to make sense.
    // Given a 3-by-1 point U, compute the intersection of the line U+t*D
    // with the plane to obtain t = -Dot(N,U-P)/Dot(N,D).  Then
    //
    //   projection(U) = P + [I - D*N^T/Dot(N,D)]*(U-P)
    //
    // A 4-by-4 homogeneous transformation representing the projection is
    //
    //       +-                               -+
    //   M = | D*N^T - Dot(N,D)*I   -Dot(N,P)D |
    //       |          0^T          -Dot(N,D) |
    //       +-                               -+
    //
    // where M applies to [U^T 1]^T by M*[U^T 1]^T.  The matrix is chosen so
    // that M[3][3] > 0 whenever Dot(N,D) < 0 (projection is onto the
    // "positive side" of the plane).

    float dotND = normal.Dot(direction);
    float dotNO = origin.Dot(normal);

    mEntry[ 0] = direction[0]*normal[0] - dotND;
    mEntry[ 1] = direction[0]*normal[1];
    mEntry[ 2] = direction[0]*normal[2];
    mEntry[ 3] = -dotNO*direction[0];
    mEntry[ 4] = direction[1]*normal[0];
    mEntry[ 5] = direction[1]*normal[1] - dotND;
    mEntry[ 6] = direction[1]*normal[2];
    mEntry[ 7] = -dotNO*direction[1];
    mEntry[ 8] = direction[2]*normal[0];
    mEntry[ 9] = direction[2]*normal[1];
    mEntry[10] = direction[2]*normal[2] - dotND;
    mEntry[11] = -dotNO*direction[2];
    mEntry[12] = 0.0f;
    mEntry[13] = 0.0f;
    mEntry[14] = 0.0f;
    mEntry[15] = -dotND;
}