double weight_l2_gauss(PCObject &o1, PCObject &o2)
{
    // l2 distance
    Eigen::MatrixXd covsum = o1.gaussian.covariance+o2.gaussian.covariance;
    Eigen::VectorXd meandiff = o1.gaussian.mean - o2.gaussian.mean;
    Eigen::MatrixXd inv = covsum.inverse();
    double det = covsum.determinant();
    double a = meandiff.transpose()*inv*meandiff;
    double l2 = 2.-2.*(1./sqrt(pow(2*pi,3)*det)) * exp(-0.5*a);
    if(l2 < 0) l2 = 0.;
    return l2;
}