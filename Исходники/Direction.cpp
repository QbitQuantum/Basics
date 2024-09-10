template<> Math::Quaternion calculate< Math::Pose >( Math::Vector< double, 3 >& orig, Math::Pose& pose1, Math::Pose& pose2 )
{
	Math::Vector< double, 3 > pos2 = pose2.translation();
	return calculate( orig, pose1, pos2 );
}