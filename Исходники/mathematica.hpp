inline Eigen::Matrix<Scalar, sizeof...(Tail) + 1, Columns>
List(const impl::RowVector<Scalar, Columns>& head, Tail... tail)
{
    Eigen::Matrix<Scalar, sizeof...(Tail) + 1, Columns> matrix;
    matrix.setZero();
    impl::fillMatrix(matrix, 0, head, tail...);
    return matrix;
}