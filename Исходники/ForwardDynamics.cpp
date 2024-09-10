/// function from Murray, Li and Sastry p.42
void ForwardDynamics::SE3exp
(Position& out_T, const Position& T0, const Vector3& w, const Vector3& vo, double dt)
{
    double norm_w = w.norm();
	
    if(norm_w < std::numeric_limits<double>::epsilon()) {
        out_T.linear() = T0.linear();
        out_T.translation() = T0.translation() + vo * dt;
    } else {
        double th = norm_w * dt;
        Vector3 w_n = w / norm_w;
        Vector3 vo_n = vo / norm_w;
        const Matrix3 R(AngleAxisd(th, w_n));
        out_T.translation() =
            R * T0.translation() + (Matrix3::Identity() - R) * w_n.cross(vo_n) + (w_n * w_n.transpose()) * vo_n * th;
        out_T.linear() = R * T0.linear();
    }
}