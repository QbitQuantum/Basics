/// Determines the goal configuration of the left arm based on the cinder block pose, calls
/// analytical I.K. to find a suitable goal arm configuration and calls RRT routine to get the
/// appropriate trajectory. Finally, using the Timer routine, displays the trajectory.
void SimTab::OnButton(wxCommandEvent &evt) {

	static int i = 0;
	i = (i + 1) % 4;

	// Set the initial config if restarting
	if(i == 3) {
		krang->setConfig(planar_ids, Eigen::Vector3d(0.0, 0.0, -M_PI_2));
		viewer->DrawGLScene();
		return;
	}

	// Get the normal and the location of the cinder block
	Eigen::Matrix4d cinderT = mWorld->getSkeleton("Cinder2")->getNode("root")->getWorldTransform();
	Eigen::Vector3d normal = -cinderT.block<3,1>(0,2);
	Eigen::Vector3d hole (cinderT(0,3), cinderT(1,3), 0.44);
	hole += normal * 0.0945;
	cout << "\nhole: " << hole.transpose() << endl;
	cout << "normal: " << normal.transpose() << endl;

	// Determine where we want Krang to be
	Eigen::Vector3d perp (-normal(1), normal(0), 0.0);
	Eigen::Vector3d goalPos = hole + normal * 0.3 + perp * 0.6;
	cout << "goalPos: " << goalPos.transpose() << endl;
	double th = atan2(normal(0), -normal(1)) + 0.1;
	Eigen::Vector3d goalConfig (goalPos(0), goalPos(1), th);

	// Determine the angle we need to be to go the goal position
	double th2 = atan2(-goalPos(0), goalPos(1));
	//cout << th2 << " " << sqrt(goalPos(0) * goalPos(0) + goalPos(1) * goalPos(1)) << " " << th << endl;


	static const double wheelRadius = 0.264;	// r, cm
	static const double rotationRadius = 0.350837; // R, cm
	double v1 = (th2 * rotationRadius) / wheelRadius;
	double v3 = (th * rotationRadius) / wheelRadius;
	double dist = sqrt(goalPos(0) * goalPos(0) + goalPos(1) * goalPos(1));
	double v2 = dist / wheelRadius;
	Eigen::Vector3d params (v1,v2,v3);
	cout << "params: " << params.transpose() << endl;

	if(i == 2) {
		cout << "th: " << th << endl;
		krang->setConfig(planar_ids, Eigen::Vector3d(goalPos(0), goalPos(1), th));
		viewer->DrawGLScene();
		return;
	}
	if(i == 0) {
		cout << "th2: " << th2 << endl;
		krang->setConfig(planar_ids, Eigen::Vector3d(0.0, 0.0, th2));
		viewer->DrawGLScene();
		return;
	}

	// Draw the robot at the goal position having just arrived
	if(i == 1) {
		krang->setConfig(planar_ids, Eigen::Vector3d(goalPos(0), goalPos(1), th2));
		viewer->DrawGLScene();
	}
}