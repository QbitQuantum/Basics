Eigen::MatrixXd get_symmetric_point(
    const Eigen::VectorXd& _normal,
    const Eigen::VectorXd& _center,
    const Eigen::MatrixXd& _points)
{
    // Assume that '_normal' is normalized.
    Eigen::MatrixXd plane_to_points = _normal * _normal.transpose() * (_points.colwise() - _center);
    Eigen::MatrixXd symmetric_point = _points - (plane_to_points * 2);

    // Debug.
    //Eigen::MatrixXd mid_points = 0.5 * (symmetric_point + _points);
    //Eigen::VectorXd distances = (mid_points.colwise() - _center).transpose() * _normal;
    //std::cout << distances.sum() / distances.rows() << std::endl;

    return symmetric_point;
}