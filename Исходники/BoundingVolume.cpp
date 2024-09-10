void BoundingVolume::transform(const Matrix& m)
{
    // Transform the bounding sphere
    m.transformPoint(center, &center);
    Vector3 translate;
    m.decompose(&translate, NULL, NULL);
    float r = radius * translate.x;
    r = std::max(radius, radius * translate.y);
    r = std::max(radius, radius * translate.z);
    radius = r;

    // Transform the bounding box
    Vector3 corners[8];
    corners[0].set(min.x, max.y, max.z);
    // Left-bottom-front.
    corners[1].set(min.x, min.y, max.z);
    // Right-bottom-front.
    corners[2].set(max.x, min.y, max.z);
    // Right-top-front.
    corners[3].set(max.x, max.y, max.z);
    // Right-top-back.
    corners[4].set(max.x, max.y, min.z);
    // Right-bottom-back.
    corners[5].set(max.x, min.y, min.z);
    // Left-bottom-back.
    corners[6].set(min.x, min.y, min.z);
    // Left-top-back.
    corners[7].set(min.x, max.y, min.z);

    // Transform the corners, recalculating the min and max points along the way.
    m.transformPoint(corners[0], &corners[0]);
    Vector3 newMin = corners[0];
    Vector3 newMax = corners[0];
    for (int i = 1; i < 8; i++)
    {
        m.transformPoint(corners[i], &corners[i]);
        updateMinMax(&corners[i], &newMin, &newMax);
    }
    min = newMin;
    max = newMax;
}