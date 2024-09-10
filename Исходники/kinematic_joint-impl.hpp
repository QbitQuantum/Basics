// static BITBOTS_INLINE Eigen::Matrix4d inverse_chain_matrix(const Eigen::Matrix4d chain_matrix) {
//     Eigen::Matrix4d inverse;
//     inverse.block<3, 3>(0, 0) = chain_matrix.block<3, 3>(0, 0).inverse();
//     inverse.col(3).head<3>() = -(inverse.block<3, 3>(0, 0) * chain_matrix.col(3).head<3>());
//     inverse.row(3) = Eigen::RowVector4d(0, 0, 0, 1);
//     return inverse;
// }
static BITBOTS_INLINE Eigen::Affine3d inverse_chain_matrix(const Eigen::Affine3d& chain_matrix) {
    return chain_matrix.inverse();
}