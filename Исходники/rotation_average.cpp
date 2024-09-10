double
RotationAverage::chordal(Sophus::SO3d *avg)
{
    double max_angle=0;
    Eigen::Matrix4d Q;
    Q.setZero();
    auto rest = rotations.begin();
    rest++;
    for(auto && t: zip_range(weights, rotations))
    {
        double w=t.get<0>();
        Sophus::SO3d& q = t.get<1>();
        Q += w * q.unit_quaternion().coeffs() * q.unit_quaternion().coeffs().transpose();
        max_angle = std::accumulate(rest, rotations.end(), max_angle,
                [&q](double max, const Sophus::SO3d& other)
                {
                return std::max(max,
                    q.unit_quaternion().angularDistance(other.unit_quaternion()));
                });
    }
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix4d> solver;
    solver.compute(Q);
    Eigen::Vector4d::Map(avg->data()) = solver.eigenvectors().col(3);
    return max_angle;
 }