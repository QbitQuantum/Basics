TransformDerivative TransformDerivative::derivativeOfInverse(const Transform& a_H_b) const
{
    Transform b_H_a = a_H_b.inverse();

    TransformDerivative ret;

    // For the sake of compact notation, we will indicated
    // a_R_b the rotational part of a_H_b, and a_O_b the translation part of a_H_b)
    Eigen::Map<const Eigen::Vector3d> d_a_O_b(this->posDerivative.data());
    Eigen::Map<const Eigen::Matrix<double,3,3,Eigen::RowMajor> > d_a_R_b(this->rotDerivative.data());

    Eigen::Map<const Eigen::Vector3d> b_O_a(b_H_a.getPosition().data());
    Eigen::Map<const Eigen::Matrix<double,3,3,Eigen::RowMajor> > b_R_a(b_H_a.getRotation().data());

    Eigen::Map<Eigen::Vector3d> d_b_O_a(ret.posDerivative.data());
    Eigen::Map<Eigen::Matrix<double,3,3,Eigen::RowMajor> > d_b_R_a(ret.rotDerivative.data());

    // ~^b \dot{R}_a = - b_R_a a_\dot{R}_b b_R_a
    d_b_R_a = -b_R_a*d_a_R_b*b_R_a;

    // ~^b \dot{O}_a = - b_R_a*(a_\dot{R}_b ~^b O_a + ~^a \dot{O}_b
    d_b_O_a = -b_R_a*(d_a_R_b*b_O_a+d_a_O_b);

    return ret;
}