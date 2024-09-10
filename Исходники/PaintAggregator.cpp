// Subtracts out the intersection of |a| and |b| from |a|, assuming |b| fully
// overlaps with |a| in either the x- or y-direction. If there is no full
// overlap, then |a| is returned.
static IntRect subtractIntersection(const IntRect& a, const IntRect& b)
{
    // boundary cases:
    if (!a.intersects(b))
        return a;
    if (b.contains(a))
        return IntRect();

    int rx = a.x();
    int ry = a.y();
    int rr = a.maxX();
    int rb = a.maxY();

    if (b.y() <= a.y() && b.maxY() >= a.maxY()) {
        // complete intersection in the y-direction
        if (b.x() <= a.x())
            rx = b.maxX();
        else
            rr = b.x();
    } else if (b.x() <= a.x() && b.maxX() >= a.maxX()) {
        // complete intersection in the x-direction
        if (b.y() <= a.y())
            ry = b.maxY();
        else
            rb = b.y();
    }
    return IntRect(rx, ry, rr - rx, rb - ry);
}