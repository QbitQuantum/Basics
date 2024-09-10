void CalibrationNode::performEstimation(){
	if(rotationRB_vec.size() < 5 ){
		std::cout << "Insufficient data" << std::endl;
		return;
	}

	//perform least squares estimation
	Matrix3f M;
	Matrix4f rbi, rbj, cbi, cbj;
	Matrix4f A, B;

	Matrix3f I;
	I.setIdentity();

	MatrixXf C(0,3), bA(0,1), bB(0,1);

	Vector3f ai, bi;

	VectorXf V_tmp;
	MatrixXf C_tmp;

	M.setZero();

	for(int i=0; i < (int)rotationRB_vec.size(); i++){
		for(int j=0; j < (int)rotationRB_vec.size(); j++){
			if(i!=j){
				rbi << rotationRB_vec[i] , translationRB_vec[i] ,  0, 0, 0, 1;
				rbj << rotationRB_vec[j] , translationRB_vec[j] ,  0, 0, 0, 1;
				A = rbj.inverse()*rbi;

				cbi << rotationCB_vec[i] , translationCB_vec[i] ,  0, 0, 0, 1;
				cbj << rotationCB_vec[j] , translationCB_vec[j] ,  0, 0, 0, 1;
				B = cbj*cbi.inverse();

				ai = getLogTheta(A.block(0,0,3,3));
				bi = getLogTheta(B.block(0,0,3,3));

				M += bi*ai.transpose();

				MatrixXf C_tmp = C;
				C.resize(C.rows()+3, NoChange);
				C << C_tmp,  Matrix3f::Identity() - A.block(0,0,3,3);

				V_tmp = bA;
				bA.resize(bA.rows()+3, NoChange);
				bA << V_tmp, A.block(0,3,3,1);

				V_tmp = bB;
				bB.resize(bB.rows()+3, NoChange);
				bB << V_tmp, B.block(0,3,3,1);

			}//end of if i!=j
		}
	}//end of for(.. i < rotationRB_vec.size(); ..)

#if ESTIMATION_DEBUG
	std::cout << "M = [ " << M << " ]; " << endl;
#endif

	EigenSolver<Matrix3f> es(M.transpose()*M);
	Matrix3cf D = es.eigenvalues().asDiagonal();
	Matrix3cf V = es.eigenvectors();

	Matrix3cf Lambda = D.inverse().array().sqrt();
	Matrix3cf Theta_X = V * Lambda * V.inverse() * M.transpose();
	std::cout << "Orientation of Camera Frame with respect to Robot tool-tip frame." << std::endl;
	std::cout << "Theta_X = [ " << Theta_X.real()  << " ]; " << endl;

	//Estimating translational offset
	for(int i=0; i < bB.rows()/3; i++){
		bB.block(i*3,0,3,1) = Theta_X.real()*bB.block(i*3,0,3,1);
	}
	bA = bA - bB; // this is d. saving memory

	std::cout << "Translation of Camera Frame with respect to Robot tool-tip frame." << std::endl;
	cout << "bX = [ " << (C.transpose()*C).inverse() * C.transpose() * bA << " ]; " << endl;

}