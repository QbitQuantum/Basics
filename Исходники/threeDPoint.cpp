double covToSDPixels(const Eigen::Matrix2d & S)
{
    const double dProductOfEigenvectors = S.determinant();
    if(IS_DEBUG) CHECK(dProductOfEigenvectors < 0, "cov matrix not positive definite");
    return pow(dProductOfEigenvectors, 0.25); //Approx. sigma in pixels
}