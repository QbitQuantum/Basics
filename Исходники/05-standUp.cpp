/// Get the joint values from the encoders and the imu and compute the center of mass as well 
void getState(Vector6d& state, double dt) {

	// Read motor encoders, imu and ft and update dart skeleton
  hw->updateSensors(dt);

	// Calculate the COM of the body
	Eigen::Vector3d comRobot = krang->getWorldCOM();
	comRobot(2) -= 0.264;
	comRobot(0) += 0.00;  
	if(dbg) cout << "comRobot: " << comRobot.transpose() << endl;

	// Get the com of the object
	Eigen::Matrix4d T = krang->getNode("lGripper")->getWorldTransform();
	Eigen::Vector3d objectCOM = T.topRightCorner<3,1>() + T.block<3,1>(0,2) * 0.20;
	if(dbg) cout << "R: " << T.topLeftCorner<3,3>() << endl;

	// Combine the two coms
	Eigen::Vector3d com = (comRobot * 145.0 + objectCOM * 13.2) / (145 + 13.2);
	if(dbg) cout << "com: " << com.transpose() << endl;

	// Update the state (note for amc we are reversing the effect of the motion of the upper body)
	state(0) = atan2(com(0), com(2));
	state(1) = hw->imuSpeed;
	state(2) = (hw->amc->pos[0] + hw->amc->pos[1]) / 2.0 + hw->imu;
	state(3) = (hw->amc->vel[0] + hw->amc->vel[1]) / 2.0 + hw->imuSpeed;
	state(4) = (hw->amc->pos[1] - hw->amc->pos[0]) / 2.0;
	state(5) = (hw->amc->vel[1] - hw->amc->vel[0]) / 2.0;
}