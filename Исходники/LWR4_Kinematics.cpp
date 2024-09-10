//------------------------------------------------------------------------------
// Constructor hard-coded for LWR4 DH
//------------------------------------------------------------------------------
LWR4Kinematics::LWR4Kinematics(KDL::Frame _tool_to_ee){

	tr_tool_to_ee = _tool_to_ee;

	// just to prevent inverting at the run time
	tr_ee_to_tool = _tool_to_ee.Inverse();

	jlim1 = 2.97; // rads = 170 degrees for joints: 1 3 5 7
	jlim2 = 2.09; // rads = 120 degrees for joints: 2 4 6

	config_fk = 0;

	n_joints = 7;

	psi_fk = 0.0;

	dbs=0.31;
	dse=0.4;
	dew=0.39;
	dwt=0.078;

	//	q_ik = std::vector<double>(7, 0.0);

	vbs = tf::Vector3(0.0,0.0,dbs);
	vwt = tf::Vector3(0.0,0.0,dwt);

};