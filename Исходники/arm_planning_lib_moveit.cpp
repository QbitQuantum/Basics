geometry_msgs::Pose MoveitPlanningInterface::transformEigenAffine3dToPose(Affine3d e) {
	Vector3d Oe;
	Matrix3d Re;
	geometry_msgs::Pose pose;
	Oe = e.translation();
	Re = e.linear();
	
	Quaterniond q(Re); // convert rotation matrix Re to a quaternion, q
	pose.position.x = Oe(0);
	pose.position.y = Oe(1);
	pose.position.z = Oe(2);
	
	pose.orientation.x = q.x();
	pose.orientation.y = q.y();
	pose.orientation.z = q.z();
	pose.orientation.w = q.w();
	
	return pose;
}