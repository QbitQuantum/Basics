	//for final project for cs7492 - implicit with conjugate gradient
	void mySpring::buildSprJpJv() {
		Eigen::Vector3d delPos = (a->getPosition() - b->getPosition());
		Eigen::Matrix3d dpdpT = delPos * delPos.transpose();

		double currLen = (delPos.norm());
		if (currLen != 0) currLen = 1.0 / currLen;     //handles if currLen is 0, Jp will be 0
		dpdpT = dpdpT*(currLen*currLen);
		Jp = (dpdpT + (Id3x3 - dpdpT)*(1 - (restLen*currLen))) * Ks;
		//Jd is constant, since kd won't change
	}