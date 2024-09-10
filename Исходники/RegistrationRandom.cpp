double transformationdiff(Eigen::Affine3d & A, Eigen::Affine3d & B, double rotationweight) {
    Eigen::Affine3d C = A.inverse()*B;
    double r = fabs(1-C(0,0))+fabs(C(0,1))+fabs(C(0,2))  +  fabs(C(1,0))+fabs(1-C(1,1))+fabs(C(1,2))  +  fabs(C(2,0))+fabs(C(2,1))+fabs(1-C(2,2));
    double t = sqrt(C(0,3)*C(0,3)+C(1,3)*C(1,3)+C(2,3)*C(2,3));
    return r*rotationweight+t;
}