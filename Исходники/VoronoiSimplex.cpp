// Compute point of a line segment that is closest to the origin
void VoronoiSimplex::computeClosestPointOnSegment(const Vector3& a, const Vector3& b, int& bitUsedVertices,
                                                  float& t) const {

    Vector3 AP = -a;
    Vector3 AB = b - a;
    decimal APDotAB = AP.dot(AB);

    // If the closest point is on the side of A in the direction of B
    if (APDotAB > decimal(0.0)) {
        decimal lengthABSquare = AB.lengthSquare();

        // If the closest point is on the segment AB
        if (APDotAB < lengthABSquare) {
            t = APDotAB / lengthABSquare;

            bitUsedVertices = 3; // 0011 (both A and B are used)

        }
        else {  // If the origin is on the side of B that is not in the direction of A
            // Therefore, the closest point is B
            t = decimal(1.0);

            bitUsedVertices = 2; // 0010 (only B is used)
        }
    }
    else {  // If the origin is on the side of A that is not in the direction of B
        // Therefore, the closest point of the line is A
        t = decimal(0.0);

        bitUsedVertices = 1; // 0001 (only A is used)
    }
}