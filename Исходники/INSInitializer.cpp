INS INSInitializer::initializeINS() const {
    // Average up all accel and mag samples
    Eigen::Vector3d y_a = mean(Eigen::Vector3d::Zero(), y_a_log.begin(), y_a_log.end());
    Eigen::Vector3d y_m = mean(Eigen::Vector3d::Zero(), y_m_log.begin(), y_m_log.end());

    // Use TRIAD to compute a rotation matrix
    Eigen::Vector3d a = -config.g_nav.normalized();
    Eigen::Vector3d a_hat = y_a.normalized();
    Eigen::Vector3d m = a.cross(config.m_nav).normalized();
    Eigen::Vector3d m_hat = a_hat.cross(y_m).normalized();
    Eigen::Matrix3d R_imu2nav =
        (Eigen::Matrix3d() << a, m, a.cross(m)).finished() *
        (Eigen::Matrix3d() << a_hat, m_hat, a_hat.cross(m_hat)).finished().transpose();

    // Sum up all the DVL readings
    Eigen::Vector4d y_d = mean(Eigen::Vector4d::Zero(), y_d_log.begin(), y_d_log.end());

    // Use least squares with the beam matrix to determine our velocity
    Eigen::Vector3d v_imu_init =
        (config.beam_mat.transpose()*config.beam_mat).lu().solve( // TODO fix guide
            config.beam_mat.transpose() * y_d);

    // Use the depth sensor to determine our z position
    double p_nav_z = -mean(0, y_z_log.begin(), y_z_log.end())
        - (R_imu2nav*config.r_imu2depth)[2];

    // Initialize an INS
    return INS(Eigen::Quaterniond(R_imu2nav),
               R_imu2nav * v_imu_init,
               Eigen::Vector3d(0, 0, p_nav_z),
               config.g_nav);
}