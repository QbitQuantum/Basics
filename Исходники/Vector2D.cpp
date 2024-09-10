double Vector2D::angleBetween(const Vector2D &a, const Vector2D &b)
{
    return atan2(cross(a, b), scalar(a, b));
}