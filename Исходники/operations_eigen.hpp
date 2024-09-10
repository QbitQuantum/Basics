typename T1::Scalar inner_prod(const Eigen::MatrixBase<T1> &x, const Eigen::MatrixBase<T2> &y) {
    return x.dot(y);
}