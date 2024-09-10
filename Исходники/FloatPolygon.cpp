static inline bool areCollinearPoints(const FloatPoint& p0, const FloatPoint& p1, const FloatPoint& p2)
{
    return !determinant(p1 - p0, p2 - p0);
}