void fundamental2essential( Eigen::Matrix3d &Fundamental, Eigen::Matrix3d &kalibration,
		        Eigen::Matrix3d &Essential)
{
    Essential = kalibration.transpose()*(Fundamental*kalibration);
    Essential = Essential/Essential(2,2);
    
    return;
}