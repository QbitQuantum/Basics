    float SupportPolygon::getSquaredDistLine(Eigen::Vector2f& p, Eigen::Vector2f& pt1, Eigen::Vector2f& pt2)
    {
        //nearestPointOnLine
        Eigen::Vector2f lp = p - pt1;
        Eigen::Vector2f dir = (pt2 - pt1);
        dir.normalize();
        float lambda = dir.dot(lp);
        Eigen::Vector2f ptOnLine = pt1 + lambda * dir;

        //distPointLine
        return (ptOnLine - p).squaredNorm();
    }