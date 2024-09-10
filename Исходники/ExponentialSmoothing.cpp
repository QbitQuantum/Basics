/** multiplication operator for scaling a pose by a scalar value */
Math::Pose operator*( const double& alpha, const Math::Pose &pose )
{
	return Math::Pose ( alpha * pose.rotation(),  alpha * pose.translation() );
}