inline double
squared_distance(const Eigen::Matrix<double, R1, C1>& v1,
                 const Eigen::Matrix<double, R2, C2>& v2) {
    check_vector("squared_distance", "v1", v1);
    check_vector("squared_distance", "v2", v2);
    check_matching_sizes("squared_distance", "v1", v1, "v2", v2);
    return (v1.transpose()-v2).squaredNorm();
}