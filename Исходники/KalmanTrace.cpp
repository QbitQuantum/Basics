float KalmanTrace::sq_distance_in_sigmas (const Observation& observation) {
    update_prediction( observation.time );

    Eigen::Matrix<double,Obs,1> expected_observation 
        = observation_matrix * prediction.position;
    Eigen::Matrix<double,Obs,Obs> covar_of_observations
        = observation_matrix * prediction.covariance
            * observation_matrix.transpose();

    Eigen::Matrix<double,Obs,Obs> covar_of_next_measurement =
            covar_of_observations + observation.covariance;

    Eigen::Matrix<double,Obs,1> difference 
        = expected_observation - observation.position;

    return difference.dot( 
        covar_of_next_measurement.inverse() * difference );
}