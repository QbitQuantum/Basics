// Compute the wrench on the wheel as an effect of the wrench acting on the sensor
void computeWheelWrench(const Vector6d& wrenchSensor, SkeletonDynamics& robot, Vector6d& wheelWrench, bool left) {
	
	// Get the position vector of the sensor with respect to the wheels
	const char* nodeName = left ? "lGripper" : "rGripper";
	Vector3d Tws = robot.getNode(nodeName)->getWorldTransform().topRightCorner<3,1>();
	if(0 && myDebug) cout << Tws.transpose() << endl;

	// Get the wrench shift operator to move the wrench from sensor origin to the wheel axis
	// TODO: This shifting is to the origin of the world frame in dart. It works now because it is not 
	// being updated by the amc encoders. We need to shift the wrench to a frame having origin at the 
	// wheel axis.
	Tws(2) -= 0.264;
	Matrix6d pTsensor_wheel = MatrixXd::Identity(6,6);
	pTsensor_wheel.bottomLeftCorner<3,3>() << 0.0, -Tws(2), Tws(1), Tws(2), 0.0, -Tws(0),
		-Tws(1), Tws(0), 0.0;

	// Shift the wrench from the sensor origin to the wheel axis
	wheelWrench = pTsensor_wheel * wrenchSensor;
}