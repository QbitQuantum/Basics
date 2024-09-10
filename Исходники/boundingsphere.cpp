void BoundingSphere::transform(const Matrix& matrix)
{
    // Translate the center point.
    matrix.transformPoint(center, &center);

    // Scale the sphere's radius by the scale fo the matrix
    Vector3 scale;
    matrix.decompose(&scale, NULL, NULL);
    float r = radius * scale.x;
    r = max(r, radius * scale.y);
    r = max(r, radius * scale.z);
    radius = r;
}