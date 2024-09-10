void RectangleHandler::initRectangle(const Eigen::VectorXd& Sw, double lambda,
		const Eigen::VectorXd& z, Eigen::VectorXd& shapeParams,
		Eigen::VectorXd& F) {

	//Get the points
	Eigen::Vector3d m1(z[0], z[1], 1);
	Eigen::Vector3d m2(z[2], z[3], 1);
	Eigen::Vector3d m3(z[4], z[5], 1);
	Eigen::Vector3d m4(z[6], z[7], 1);

	Eigen::Vector3d Ct(Sw[0], Sw[1], Sw[2]);
	Eigen::Quaterniond Cq(Sw[3], Sw[4], Sw[5], Sw[6]);

	//compute normals
	double c2 = (m1.cross(m3).transpose() * m4)[0]
			/ (m2.cross(m3).transpose() * m4)[0];
	double c3 = (m1.cross(m3).transpose() * m2)[0]
			/ (m4.cross(m3).transpose() * m2)[0];

	Eigen::Vector3d n2 = c2 * m2 - m1;
	Eigen::Vector3d n3 = c3 * m4 - m1;

	//Compute rotation matrix columns
	Eigen::Vector3d R1 = _K.inverse() * n2;
	R1 = R1 / R1.norm();

	Eigen::Vector3d R2 = _K.inverse() * n3;
	R2 = R2 / R2.norm();

	Eigen::Vector3d R3 = R1.cross(R2);

	//Compute frame quaternion
	Eigen::Matrix3d R;
	R << R1, R2, R3;

	const Eigen::Quaterniond qOC(R);

	Eigen::Quaterniond Fqhat = Cq * qOC;

	//Compute frame transaltion
	Eigen::Matrix3d omega = _K.transpose().inverse() * _K.inverse();
	double ff = sqrt(
			(n2.transpose() * omega * n2)[0] / (n3.transpose() * omega * n3)[0]);

	Eigen::Vector3d CtOhat = lambda * _K.inverse() * m1;
	Eigen::Vector3d Fthat = Ct + Cq.toRotationMatrix() * CtOhat;

	//compute shape parameters
	Eigen::Vector3d X = _K * R1;
	Eigen::Vector3d Y = c2 * lambda * m2 - lambda * m1;

	double w = ((X.transpose() * X).inverse() * X.transpose() * Y)[0];
	double h = w / ff;

	//Write the results
	shapeParams << w, h;
	F << Fthat[0], Fthat[1], Fthat[2], Fqhat.w(), Fqhat.x(), Fqhat.y(), Fqhat.z();

}