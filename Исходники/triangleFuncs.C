// Intersect triangle with bounding box. Return true if
// any of the faces of bb intersect triangle.
// Note: so returns false if triangle inside bb.
bool Foam::triangleFuncs::intersectBb
(
    const point& p0,
    const point& p1,
    const point& p2,
    const treeBoundBox& cubeBb
)
{
    const vector p10 = p1 - p0;
    const vector p20 = p2 - p0;

    // cubeBb points; counted as if cell with vertex0 at cubeBb.min().
    const point& min = cubeBb.min();
    const point& max = cubeBb.max();

    const point& cube0 = min;
    const point  cube1(min.x(), min.y(), max.z());
    const point  cube2(max.x(), min.y(), max.z());
    const point  cube3(max.x(), min.y(), min.z());

    const point  cube4(min.x(), max.y(), min.z());
    const point  cube5(min.x(), max.y(), max.z());
    const point  cube7(max.x(), max.y(), min.z());

    //
    // Intersect all 12 edges of cube with triangle
    //

    point pInter;
    pointField origin(4);
    // edges in x direction
    origin[0] = cube0;
    origin[1] = cube1;
    origin[2] = cube5;
    origin[3] = cube4;

    scalar maxSx = max.x() - min.x();

    if (intersectAxesBundle(p0, p10, p20, 0, origin, maxSx, pInter))
    {
        return true;
    }

    // edges in y direction
    origin[0] = cube0;
    origin[1] = cube1;
    origin[2] = cube2;
    origin[3] = cube3;

    scalar maxSy = max.y() - min.y();

    if (intersectAxesBundle(p0, p10, p20, 1, origin, maxSy, pInter))
    {
        return true;
    }

    // edges in z direction
    origin[0] = cube0;
    origin[1] = cube3;
    origin[2] = cube7;
    origin[3] = cube4;

    scalar maxSz = max.z() - min.z();

    if (intersectAxesBundle(p0, p10, p20, 2, origin, maxSz, pInter))
    {
        return true;
    }


    // Intersect triangle edges with bounding box
    if (cubeBb.intersects(p0, p1, pInter))
    {
        return true;
    }
    if (cubeBb.intersects(p1, p2, pInter))
    {
        return true;
    }
    if (cubeBb.intersects(p2, p0, pInter))
    {
        return true;
    }

    return false;
}