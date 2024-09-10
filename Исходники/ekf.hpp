    void EKF::correct(Eigen::Vector2d z_i)
    {
        // measurement matrix
        Eigen::Matrix2d I = Eigen::Matrix2d::Identity();
        Eigen::Matrix2d H = Eigen::Matrix2d::Identity();

        // innovation residual
        Eigen::Vector2d y = z_i - H * this->x;

        // innovation covariance
        Eigen::Matrix2d S = H * this->P * H.transpose() + this->R;

        // Kalman gain
        Eigen::Matrix2d K = this->P * H.transpose() * S.inverse();

        // updated state
        this->x = this->x + K * y;

        // updated covariance
        this->P = (I - K * H) * this->P;


    }