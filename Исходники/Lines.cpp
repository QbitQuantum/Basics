/**
 * @brief findIntersection for 2D lines. Can handle pll lines (return nothing)
 * @param other
 * @return
 */
optional<const C2dImagePointPx> C2dLine::findIntersection(const C2dLine & other) const
{
    Eigen::Matrix<double, 2, 2> directions;
    directions.block<2,1>(0,0) = direction;
    directions.block<2,1>(0,1) = -other.direction;

    if(fabs(directions.determinant()) < 1e-8)//Should usually be about 1
        return optional<const C2dImagePointPx>();

    const C2dImagePointPx diff = other.pointOnLine - pointOnLine;

    const TEigen2dPoint lambda_mu = directions.inverse() * diff;
    const C2dImagePointPx pointOnLine = point(lambda_mu(0));
    if(IS_DEBUG) CHECK(!zero((other.point(lambda_mu(1)) - pointOnLine).squaredNorm()), "findIntersection failed (parallel lines?)");

    return optional<const C2dImagePointPx>(pointOnLine);
}