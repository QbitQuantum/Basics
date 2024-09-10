void TriskarSmallBody::calculateDesireAngle(Quaternion parameter){
	tf::Quaternion q(parameter.getX(),parameter.getY(),parameter.getZ(),parameter.getW());
	tf::Matrix3x3 m(q);
	double roll, pitch, yaw;
	m.getRPY(roll, pitch, yaw);
	this->desire_yaw = yaw;
}