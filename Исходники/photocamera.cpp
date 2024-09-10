Eigen::MatrixXf PhotoCamera::getPseudoInverse()
{
    Eigen::MatrixXf P = intrinsicMatrix*extrinsicMatrix.matrix();
    Eigen::MatrixXf Pt = P.transpose();
    Eigen::MatrixXf pseudoInverse = Pt*(P*Pt).inverse();
    return pseudoInverse;
}