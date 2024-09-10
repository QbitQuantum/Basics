bool FeatureCoordinates::getDepthFromTriangulation(const FeatureCoordinates& other, const V3D& C2rC2C1, const QPD& qC2C1, FeatureDistance& d) {
    Eigen::Matrix<double,3,2> B;
    B <<  qC2C1.rotate(get_nor().getVec()), other.get_nor().getVec();
    const Eigen::Matrix2d BtB = B.transpose() * B;
    if(BtB.determinant() < 0.000001) { // Projection rays almost parallel.
        return false;
    }
    const Eigen::Vector2d dv = - BtB.inverse() * B.transpose() * C2rC2C1;
    d.setParameter(fabs(dv[0]));
    return true;
}