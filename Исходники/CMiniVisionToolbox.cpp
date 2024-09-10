const double CMiniVisionToolbox::getTransformationDelta( const Eigen::Isometry3d& p_matTransformationFrom, const Eigen::Isometry3d& p_matTransformationTo )
{
    //ds compute pose change
    const Eigen::Isometry3d matTransformChange( p_matTransformationTo*p_matTransformationFrom.inverse( ) );

    //ds check point
    const Eigen::Vector4d vecSamplePoint( 40.2, -1.25, 2.5, 1.0 );
    double dNorm( vecSamplePoint.norm( ) );
    const Eigen::Vector4d vecDifference( vecSamplePoint-matTransformChange*vecSamplePoint );
    dNorm = ( dNorm + vecDifference.norm( ) )/2;

    //ds return norm
    return ( std::fabs( vecDifference(0) ) + std::fabs( vecDifference(1) ) + std::fabs( vecDifference(2) ) )/dNorm;
}