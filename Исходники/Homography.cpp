Eigen::Matrix3f Homography::calcHomography( const Eigen::Isometry3f &camA2plane, const Eigen::Isometry3f &camB2plane ) const
{
    // calculate the plane normal (z-vector) from the point of camB
    Eigen::Vector3f n = camB2plane.rotation().transpose() * -Eigen::Vector3f::UnitZ();

    // calculate the distance from camB to plane
    float d = camB2plane.inverse().translation().dot( n );

    // get transform from camB to camA
    Eigen::Isometry3f camBtoCamA = camA2plane.inverse() * camB2plane;

    // get the homography
    return calcHomography( camBtoCamA, n, d );
}