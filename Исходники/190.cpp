// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
// **use LinesParallel and LinesColliner to detect wether they intersect
point ComputeLineIntersection(point a, point b, point c, point d)
{
    b = b - a ;
    d = c - d ;
    c = c - a ;
    assert( b.dot(b) > EPS && d.dot(d) > EPS);
    return a + b* c.cross(d) / b.cross(d) ;
}