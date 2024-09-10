Scalar func(
        const Eigen::Matrix<Scalar, -1, 1> &beta,
        const Eigen::Matrix<Scalar, -1, 1> &x)
{
    return beta.dot(x);
}