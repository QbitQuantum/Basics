inline
typename Eigen::internal::scalar_product_traits<
    typename Eigen::internal::traits<Derived>::Scalar,
    typename Eigen::internal::traits<OtherDerived>::Scalar
>::ReturnType
static dot(
    const Eigen::MatrixBase<Derived>& mat,
    const Eigen::MatrixBase<OtherDerived>& other) {
    return mat.dot(other);
}