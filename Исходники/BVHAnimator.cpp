void BVHAnimator::solveLeftArm(int frame_no, float scale, float x, float y, float z)
{
    _bvh->quaternionMoveTo(frame_no, scale);      
    // NOTE: you can use either matrix or quaternion to calculate the transformation
	float *LArx, *LAry, *LArz, *LFAry;
	
	float *mdata = _bvh->getMotionDataPtr(frame_no);
	// 3 channels - Xrotation, Yrotation, Zrotation
    // extract value address from motion data        
    CHANNEL *channel = larm->channels[0];
	LArx = &mdata[channel->index];
	channel = larm->channels[1];
	LAry = &mdata[channel->index];
	channel = larm->channels[2];
	LArz = &mdata[channel->index];

	channel = lforearm->channels[1];
	LFAry = &mdata[channel->index];
    
    cout << "Solving inverse kinematics..." << endl;
    clock_t start_time = clock();

    // -------------------------------------------------------
    // TODO: [Part 3] - Inverse Kinematics
    //
    // Put your code below
    // -------------------------------------------------------

	// 1. Compute Jacobian
	// 2. Take the inverse of the Jacobian
	// 3. Compute Changes in DOFS. dtheta = J-1 * de
	// 4. Apply the changes to DOFs and continue

	float dtheta = 0.01;
	int counter = 0;
	float error;

	//glm::vec3 startPos = lhand->transform.

	do {
	
		glm::vec3 endEffectorPos = lhand->transform.translation;

		// Take a theoretical step
		*LArx += glm::degrees(dtheta);
		*LAry += glm::degrees(dtheta);
		*LArz += glm::degrees(dtheta);
		*LFAry += glm::degrees(dtheta);
		_bvh->quaternionMoveTo(frame_no, scale);

		// Get the difference between end effector and theoretical end effector (with small theta applied)
		glm::vec3 endEffectorPosNew = lhand->transform.translation;
		glm::vec3 de = endEffectorPosNew - endEffectorPos;

		// Move back, we only want the theoretical difference
		*LArx -= glm::degrees(dtheta);
		*LAry -= glm::degrees(dtheta);
		*LArz -= glm::degrees(dtheta);
		*LFAry -= glm::degrees(dtheta);
		_bvh->quaternionMoveTo(frame_no, scale);	


		// Compute Jacobian
		Eigen::MatrixXf J = Eigen::MatrixXf::Zero(3, 4);

		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 4; col++) {
				J(row, col) = de[row] / dtheta;
			}
		}

		// Trouble calculating pseudo inverse here.. Fallback with transpose instead
		//Eigen::MatrixXf J_inverse = J.transpose() * (J * J.transpose()).inverse();
		//Eigen::MatrixXf J_inverse = (J.transpose() * J).inverse() * J.transpose();
		Eigen::MatrixXf J_inverse = J.transpose();
		//std::cout << " J_inverse " << J_inverse << std::endl;

		// Compute changes in DOFS through jacobian pseudo inverse method
		Eigen::VectorXf de_2 = Eigen::VectorXf::Zero(3, 1);
		de_2(0) = x - endEffectorPos.x;
		de_2(1) = y - endEffectorPos.y;
		de_2(2) = z - endEffectorPos.z;
		Eigen::VectorXf thetaChange = J_inverse * de_2;

		// Apply the changes in angles
		*LArx += glm::degrees(thetaChange(0));
		*LAry += glm::degrees(thetaChange(1));
		*LArz += glm::degrees(thetaChange(2));
		*LFAry += glm::degrees(thetaChange(3));

		_bvh->quaternionMoveTo(frame_no, scale);

		counter++;
		error = glm::abs(endEffectorPos.x - x) + glm::abs(endEffectorPos.y - y) + glm::abs(endEffectorPos.z - z);

	} while (counter < 1000 && error > 0.003); // Keep looping while error is bigger than threshhold or limit reached..


    // ----------------------------------------------------------
    // Do not touch
    // ----------------------------------------------------------
    clock_t end_time = clock();
    float elapsed = (end_time - start_time) / (float)CLOCKS_PER_SEC;
    cout << "Solving done in " << elapsed * 1000 << " ms." << endl;
}