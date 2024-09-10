// FloatRect::intersects does not consider horizontal or vertical lines (because of isEmpty()).
// So special-case handling of such lines.
static bool intersectsAllowingEmpty(const FloatRect& r, const FloatRect& other)
{
    if (r.isEmpty() && other.isEmpty())
        return false;
    if (r.isEmpty() && !other.isEmpty()) {
        return (other.contains(r.x(), r.y()) && !other.contains(r.maxX(), r.maxY()))
               || (!other.contains(r.x(), r.y()) && other.contains(r.maxX(), r.maxY()));
    }
    if (other.isEmpty() && !r.isEmpty())
        return intersectsAllowingEmpty(other, r);
    return r.intersects(other);
}