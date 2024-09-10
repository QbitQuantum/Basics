    static void qprod(const Eigen::Vector4d & q, const Eigen::Vector4d & p, Eigen::Vector4d & prod_result) {
        double a=q(0);
        Eigen::Vector3d v = q.segment(1, 3); //coefficients q
        double x=p(0);
        Eigen::Vector3d u = p.segment(1, 3); //coefficients p

        prod_result << a*x-v.transpose()*u, (a*u+x*v) + v.cross(u);
    }