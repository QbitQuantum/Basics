double BSpline::curvature(double u) const
{
	Point V = speed(u);
	Point A = acceleration(u);
	double vel = V.norm();
    if (fabs(vel)>1e-5) {
        return (V.cross(A)).norm() / (vel*vel*vel);
    } else {
        return 0.0;
    }
}