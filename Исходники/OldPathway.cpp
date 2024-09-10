Vector3 
OpenSteer::Old::PolylinePathway::mapPointToPath (const Vector3& point,
                                                 Vector3& tangent,
                                                 float& outside)
{
    float d;
    float minDistance = FLT_MAX;
    Vector3 onPath;

    // loop over all segments, find the one nearest to the given point
    for (int i = 1; i < pointCount; i++)
    {
        segmentLength = lengths[i];
        segmentNormal = normals[i];
        d = pointToSegmentDistance (point, points[i-1], points[i]);
        if (d < minDistance)
        {
            minDistance = d;
            onPath = chosen;
            tangent = segmentNormal;
        }
    }

    // measure how far original point is outside the Pathway's "tube"
    outside = onPath.distance(point) - radius;

    // return point on path
    return onPath;
}