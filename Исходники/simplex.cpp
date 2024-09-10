// Add a new support point of (A-B) into the simplex
/// suppPointA : support point of object A in a direction -v
/// suppPointB : support point of object B in a direction v
/// point      : support point of object (A-B) => point = suppPointA - suppPointB
void Simplex::addPoint(const Vector3& point, const Vector3& suppPointA, const Vector3& suppPointB) {
    assert(!isFull());

    mLastFound = 0;
    mLastFoundBit = 0x1;

    // Look for the bit corresponding to one of the four point that is not in
    // the current simplex
    while (overlap(mBitsCurrentSimplex, mLastFoundBit)) {
        mLastFound++;
        mLastFoundBit <<= 1;
    }

    assert(mLastFound < 4);

    // Add the point into the simplex
    mPoints[mLastFound] = point;
    mPointsLengthSquare[mLastFound] = point.dot(point);
    mAllBits = mBitsCurrentSimplex | mLastFoundBit;

    // Update the cached values
    updateCache();
    
    // Compute the cached determinant values
    computeDeterminants();
    
    // Add the support points of objects A and B
    mSuppPointsA[mLastFound] = suppPointA;
    mSuppPointsB[mLastFound] = suppPointB;
}