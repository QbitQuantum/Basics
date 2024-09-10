double GeometryUtils::angleLike(const Eigen::Vector2d & u, const Eigen::Vector2d & v)
{
    // assume u and v are unitary
    /*
    double lu = length(u);
    if(lu>0) u = 1/lu * u;
    double lv=length(v);
    if(lv>0) v = 1/lv * v;
    */
    
    double dot_ = u.dot(v);
    double det_ = u[0]*v[1] - u[1]*v[0];
    double signDet = 1;
    if(det_ < 0) signDet = -1;
    return 2 - signDet*(dot_+1);
}