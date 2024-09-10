void GenericDistanceConstraint::gradientFct(
    const unsigned int i,
    const unsigned int numberOfParticles,
    const float mass[],
    const Eigen::Vector3f x[],
    void *userData,
    Eigen::Matrix<float, 1, 3> &jacobian)
{
    Eigen::Vector3f n = x[i] - x[1 - i];
    n.normalize();
    jacobian = n.transpose();
}