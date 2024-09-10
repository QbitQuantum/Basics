// see Welzl, Emo. Smallest enclosing disks (balls and ellipsoids). Springer Berlin Heidelberg, 1991.
void cv::minEnclosingCircle( InputArray _points, Point2f& _center, float& _radius )
{
    Mat points = _points.getMat();
    int count = points.checkVector(2);
    int depth = points.depth();
    Point2f center;
    float radius = 0.f;
    CV_Assert(count >= 0 && (depth == CV_32F || depth == CV_32S));

    _center.x = _center.y = 0.f;
    _radius = 0.f;

    if( count == 0 )
        return;

    bool is_float = depth == CV_32F;
    const Point* ptsi = points.ptr<Point>();
    const Point2f* ptsf = points.ptr<Point2f>();

    // point count <= 3
    if (count <= 3)
    {
        Point2f ptsf3[3];
        for (int i = 0; i < count; ++i)
        {
            ptsf3[i] = (is_float) ? ptsf[i] : Point2f((float)ptsi[i].x, (float)ptsi[i].y);
        }
        findEnclosingCircle3pts_orLess_32f(ptsf3, count, center, radius);
        _center = center;
        _radius = radius;
        return;
    }

    if (is_float)
    {
        findMinEnclosingCircle<Point2f>(ptsf, count, center, radius);
#if 0
        for (size_t m = 0; m < count; ++m)
        {
            float d = (float)norm(ptsf[m] - center);
            if (d > radius)
            {
                printf("error!\n");
            }
        }
#endif
    }
    else
    {
        findMinEnclosingCircle<Point>(ptsi, count, center, radius);
#if 0
        for (size_t m = 0; m < count; ++m)
        {
            double dx = ptsi[m].x - center.x;
            double dy = ptsi[m].y - center.y;
            double d = std::sqrt(dx * dx + dy * dy);
            if (d > radius)
            {
                printf("error!\n");
            }
        }
#endif
    }
    _center = center;
    _radius = radius;
}