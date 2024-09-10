SkScalar SkPoint::distanceToLineBetweenSqd(const SkPoint& a,
                                           const SkPoint& b,
                                           Side* side) const {

    SkVector u = b - a;
    SkVector v = *this - a;

    SkScalar uLengthSqd = u.lengthSqd();
    SkScalar det = u.cross(v);
    if (side) {
        SkASSERT(-1 == SkPoint::kLeft_Side &&
                  0 == SkPoint::kOn_Side &&
                  1 == kRight_Side);
        *side = (Side) SkScalarSignAsInt(det);
    }
    return SkScalarMulDiv(det, det, uLengthSqd);
}