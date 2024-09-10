VectorXd rigidBodyDynamics::f(VectorXd x) {
	Vector3d dr, dv, da, dw;
	Matrix<double,12,12> lambda, dLambda;
	VectorXd vec_dLambda;

	int vecsize;
	if (covProp) {
		vecsize = 90;
	} else {
		vecsize = 12;
	}

	VectorXd dx(vecsize);

	Vector3d r = x.segment<3>(0);
	Vector3d v = x.segment<3>(3);
	Vector3d a = x.segment<3>(6);
	Vector3d w = x.segment<3>(9);

	MatrixXd Bw = getBw();
	Matrix3d J = _ir.getJ();


	//Nonlinear State Model \dot x = f(x)

	/*
	 * 	\mathbf{\dot r} = \mathbf{v}
	 */
	dr = v;

	/*
	 * 	\mathbf{\dot v} = 0
	 */
	dv = Vector3d::Zero();

	/*
	 * \frac{d \mathbf{a}_p}{dt} =
	 * 			\frac{1}{2}\left(\mathbf{[\omega \times]} +
	 * 			\mathbf{\omega} \cdot \mathbf{\bar q} \right) \mathbf{a}_p +
	 * 			\frac{2 q_4}{1+q_4} \mathbf{\omega}
	 */
	double c1, c2, c3;
	c1 = 0.5;
	c2 = 0.125 * w.dot(a);		//NEW simplification
	c3 = 1 - a.dot(a)/16;
	da = -c1 * w.cross(a) + c2* a + c3 * w;

	/*
	 * \dot \mathbf{w} = -\mathbf{J}^{-1} \mathbf{\omega} \times \mathbf{J} \mathbf{\omega}
	 */
	dw = - J.inverse() * w.cross(J * w);

	if (covProp) {

		//Covariance Propagation according to Lyapunov function
		//see Brown & Hwang pg 204

		//Compute Linear transition matrix
		Matrix<double,12,12> A = Matrix<double,12,12>::Zero();

		//position derivative
		A.block<3,3>(0,3) = Matrix<double,3,3>::Identity();

		//mrp kinematics
		A.block<3,3>(6,6) = -0.5*crossProductMat(w) + w.dot(a)/8 * Matrix3d::Identity();
		A.block<3,3>(6,9) = (1-a.dot(a/16))*Matrix3d::Identity();

		//angular velocity dynamics
		A.block<3,3>(9,9) = - J.inverse() * crossProductMat(w) * J;


		lambda = vec2symmMat(x.segment<78>(12));
		dLambda = A * lambda + lambda *A.transpose() + Bw * _Q * Bw.transpose();
		vec_dLambda = symmMat2Vec(dLambda);
	}

	//write to dx
	dx.segment<3>(0) = dr;
	dx.segment<3>(3) = dv;
	dx.segment<3>(6) = da;
	dx.segment<3>(9) = dw;
	if(covProp){
		dx.segment<78>(12) = vec_dLambda;
	}

	return dx;
}