void ExtendedKalmanFilter::correctionStep(const Eigen::Vector3f& measurement, const Eigen::Vector3f& global_marker_pose){  // compare expected and measured values, update state and uncertainty


    // compute expected measurement:
    Vector3f z_exp; // z_exp = h(x)
    z_exp(0) = cos(state(2))*(global_marker_pose(0)- state(0)) + sin(state(2))*(global_marker_pose(1)-state(1));
    z_exp(1) = -sin(state(2))*(global_marker_pose(0) -state(0)) + cos(state(2))*(global_marker_pose(1)-state(1));
    z_exp(2) =  global_marker_pose(2)-state(2);

    Matrix3f H; // dh/dx
    H << -cos(state(2)), -sin(state(2)), -sin(state(2))*(global_marker_pose(0) - state(0)) + cos(state(2))*(global_marker_pose(1)-state(1)),
            sin(state(2)), -cos(state(2)), -cos(state(2))*(global_marker_pose(0) -state(0)) - sin(state(2))*(global_marker_pose(1)-state(1)),
            0,                  0, -1;

    // cout << "H: " << endl << H << endl;

    Matrix3f K = sigma * H.transpose() * ((H * sigma * H.transpose() + R).inverse()); // Kalman Gain

    // compute the difference between expectation and observation
    Vector3f z_diff = measurement - z_exp;
    // normalize angle
    z_diff(2) = atan2(sin(z_diff(2)),cos(z_diff(2)));

    // cout << "z_exp: " << z_exp(0) << " "<< z_exp(1) << " "<< z_exp(2) << endl;
    // cout << "diff: " << z_diff(0) << " "<< z_diff(1) << " "<< z_diff(2) << endl;

    // correct pose estimate
    state = state + K*( z_diff );
    sigma = (Matrix3f::Identity() - K*H)*sigma;


}