void poseJacobian(const Eigen::Matrix3d& rotation, Eigen::Matrix<double, 6, 6>& jac, const double rot_angle_threshold)
{
	Eigen::Matrix3d i3 = Eigen::Matrix3d::Identity();

	// convert rotation matrix into axis-angle representation
	double rot_angle;
	Eigen::Vector3d rot_axis;
	getAngleAxis(rotation.transpose(), rot_angle, rot_axis);

	// create the rotation jacobian
	Eigen::Matrix3d L_theta_u;

	double sinc_part;
	sinc_part = sva::sinc(rot_angle)/std::pow(sva::sinc(rot_angle/2.), 2);

	Eigen::Matrix3d axis_antisym;
	getSkewSym(rot_axis, axis_antisym);

	L_theta_u = i3 - rot_angle*0.5*axis_antisym + (1-(sinc_part))*axis_antisym*axis_antisym;
	jac << L_theta_u, Eigen::Matrix3d::Zero(),
				 Eigen::Matrix3d::Zero(), rotation.transpose();
}