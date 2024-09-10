RobotInterface::RobotInterface(PolyDriver* rd, IPositionControl* p, IVelocityControl* v, IEncoders* e, BufferedPort<Vector>* tdp,
							   std::vector<bool>& af, std::vector<bool>& aj) :
				robotDevice(rd),
				pos(p),
				vel(v),
				encs(e),
				tactileDataPort(tdp),
				activeFingers(af),
				activeJoints(aj),
				jointsNumber(0),
				activeFingersNumber(0),
				activeJointsNumber(0),
				iteration(0)

{
	Network yarp;

	// acquire the number of joints
	if(!pos->getAxes(&jointsNumber)) printf("ERROR: impossible to get the number of joints\n");

	// retrieve the number of active fingers
	for(unsigned int i = 0; i < activeFingers.size(); i++)
	{
		if(activeFingers[i] == true) activeFingersNumber++;
	}

	// retrieve the number of active joints
	for(unsigned int i = 0; i < activeJoints.size(); i++)
	{
		if(activeJoints[i] == true) activeJointsNumber++;
	}

	// go to home position (only for simulation, the real robot should be positioned manually)
	Vector home = Vector(jointsNumber, HOME_POSITION_VECTOR);
	positionMoveHand(home);

	// resize vectors so that they are coherent with the number of joints
	homePosition.resize(jointsNumber);
	
	// save the current joint position as an home position for each trial
	encs->getEncoders(homePosition.data());

	// debug
	printf("HOME POSITION:\t");
	for(int p = 0; p < jointsNumber; p++) printf("%f ", homePosition(p));

	// rpc connection for calibration
	rpcSkin.open(RPC_CLIENT_PORT.c_str());
	yarp.connect(RPC_CLIENT_PORT.c_str(), RPC_SERVER_PORT.c_str());
}