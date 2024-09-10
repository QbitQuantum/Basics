void PointsKalmanFilterPredictor::predict(double time, const std::vector<Eigen::Vector3d> &u, std::vector<Eigen::Matrix<double, 6, 1> >& mu, std::vector<Eigen::Matrix<double, 6, 6> >& sigma)
{
    if (time == 0.)
    {
        mu = mus_;
        sigma = sigmas_;
    }
    else
    {
        Eigen::Matrix<double, 6, 6> A;
        Eigen::Matrix<double, 6, 3> B;

        A.setIdentity();
        A.block(0, 3, 3, 3) = Eigen::Matrix3d::Identity() * time;

        B.block(0, 0, 3, 3).setIdentity();
        B.block(3, 0, 3, 3) = Eigen::Matrix3d::Identity() * time;

        mu.resize(mus_.size());
        sigma.resize(sigmas_.size());

        for (int i=0; i<mu.size(); i++)
        {
            mu[i] = A * mus_[i] + B * u[i];
            sigma[i] = A * sigmas_[i] * A.transpose() + R_;
        }
    }
}