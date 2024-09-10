/**
 * @brief DiagonalMatrix creates a diagonal matrix.
 * @param D a vector of size 3.
 * @return It returns a diagonal matrix.
 */
Eigen::Matrix3d DiagonalMatrix(Eigen::Vector3d D)
{
    Eigen::Matrix3d ret;

    ret.setZero();
    ret(0, 0) = D[0];
    ret(1, 1) = D[1];
    ret(2, 2) = D[2];

    return ret;
}