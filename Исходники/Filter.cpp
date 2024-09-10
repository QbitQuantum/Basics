Eigen::Matrix4d Filter::omegaMatrix(const Eigen::Vector3d vec) {
    Eigen::Matrix4d mat;
    mat.block<3, 3>(0, 0) = Filter::crossMatrix(-1*vec);
    mat.block<1, 3>(3, 0) = -1*(vec.transpose());
    mat.block<3, 1>(0, 3) = vec;
    mat(3, 3) = 0;
    return mat;
}