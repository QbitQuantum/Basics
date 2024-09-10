Polyangle Polyangle::getIncircle(int definition) const
{
    float pi = 3.14159265358979323846;
    Vector2D center = getCentre();
    QVector<Vector2D> newPoints;
    float radius = std::numeric_limits<float>::max();
    for (int i = 0; i < lesPoints.size(); i++)
    {
        Vector2D segment = (lesPoints[(i+1)%lesPoints.size()]-lesPoints[i]);
        segment.normalize();
        float scalar = (center-lesPoints[i])* segment;
        Vector2D nearestPoint = segment * scalar+lesPoints[i];
        float distance = center.distanceToPoint2D(nearestPoint);
        if (distance < radius)
            radius = distance;
    }

    for (int i=0; i < definition; i++)
    {
        float x = cos(2*pi*i/definition)*radius;
        float y = sin(2*pi*i/definition)*radius;
        newPoints << center + Vector2D(x, y);
    }

    return Polyangle(newPoints);

}