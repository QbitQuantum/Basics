void ChainKinematics::getXInv(double (&t)[3], double (&rot)[9], const double* q, const int segmentNr) const {

	int i,j;

	KDL::JntArray qJA(Njnt_);
	for(i=0; i<Njnt_; i++)
		qJA(i) = q[i];

	KDL::Frame frame;

	//compute forward kinematics
	checkSegmentNr(segmentNr);
	if(fksolverPos_->JntToCart(qJA, frame, segmentNr) < 0) {
		std::cerr << "ERROR: [ChainKinematics][getXInv] something went wrong during JntToCart! Exiting!" << std::endl;
		exit(-1);
	}

    //get inverse transformation
    frame = frame.Inverse();

	for(i=0; i<3; i++) {
		t[i] = frame.p(i);
		for(j=0; j<3; j++)
			rot[i*3+j] = frame.M(i,j);
	}

}