drag::drag(const Eigen::Quaterniond& q, const Eigen::Vector3d& v, const Eigen::Vector3d& w, const Eigen::Vector3d& x, const Eigen::Vector3d& n, double c, double a)
    : q(q)
    , v(v)
    , w(w)
    , x(x)
    , n(n)
    , t(x.cross(n))
    , c(c)
    , a(a)
{
}