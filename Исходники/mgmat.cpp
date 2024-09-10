Matrix2d Matrix2d::transformWith2P(const Point2d& from1, const Point2d& from2,
                                   const Point2d& to1, const Point2d& to2)
{
    if (from1 == from2 || to1 == to2
        || from1.isDegenerate() || from2.isDegenerate() || to1.isDegenerate() || to2.isDegenerate()) {
        return Matrix2d::kIdentity();
    }
    return (translation(to1 - from1)
            * scaling(to2.distanceTo(to1) / from2.distanceTo(from1), to1)
            * rotation((to2 - to1).angle2() - (from2 - from1).angle2(), to1));
}