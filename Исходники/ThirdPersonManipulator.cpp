Vector3 UIGeom::segmentNormal(const LineSegment& seg, const Vector3& eye) {
    Vector3 E = eye - seg.point(0);
    Vector3 V = seg.point(1) - seg.point(0);
    Vector3 U = E.cross(V);
    Vector3 N = V.cross(U).direction();
    return N;
}