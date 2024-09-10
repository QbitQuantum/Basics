MatrixXd MinEnFilter::DAk(const MatrixXd& Gk, const MatrixXd& Disps_inhom, int direction) {
	MatrixXd Ones = MatrixXd::Ones(1,4);
	MatrixXd Eaux = MatrixXd::Identity(6,6);
	Matrix4d eta = MEFcommon::matSE(Eaux.col(direction-1));
	MatrixXd iEg = (currG.E.lu().solve(Gk.transpose())).transpose();
	VectorXd kappa = iEg.col(2);
	MatrixXd h = iEg.leftCols(2).cwiseQuotient(kappa*MatrixXd::Ones(1,2));
	MatrixXd z = Disps_inhom.leftCols(2) - h;
	VectorXd kappaM1 = kappa.cwiseInverse();
	VectorXd kappaM2 = (kappa.cwiseProduct(kappa)).cwiseInverse();
	VectorXd kappaM3 = (kappa.cwiseProduct(kappa.cwiseProduct(kappa))).cwiseInverse();	
	MatrixXd lambda = ((currG.E.lu().solve(eta))*(iEg.transpose())).transpose();
	VectorXd xi = (lambda.col(2)).cwiseProduct(kappaM2);
	
	// first part of Hessian
	VectorXd zeta1 = -2* kappaM3.cwiseProduct((lambda.col(2)).cwiseProduct(iEg.col(0)));
	VectorXd zeta2 = -2 * kappaM3.cwiseProduct((lambda.col(2)).cwiseProduct(iEg.col(1)));
	VectorXd eta1 = kappaM2.cwiseProduct(lambda.col(0));
	VectorXd eta2 = kappaM2.cwiseProduct(lambda.col(1));
	VectorXd a31 = zeta1 + eta1;
	VectorXd a32 = zeta2 + eta2;
	MatrixXd b1row = q1/nPoints * ((z.col(0))*Ones).cwiseProduct(iEg);
	MatrixXd b2row = q2/nPoints * ((z.col(1))*Ones).cwiseProduct(iEg);	
	MatrixXd c1row = ((xi * Ones).cwiseProduct(b1row)).colwise().sum();
	MatrixXd c2row = ((xi * Ones).cwiseProduct(b2row)).colwise().sum();
	MatrixXd aux1(nPoints,4);
	aux1 << (a31.cwiseProduct(b1row.col(0)) + a32.cwiseProduct(b2row.col(0))) , (a31.cwiseProduct(b1row.col(1)) + a32.cwiseProduct(b2row.col(1))), (a31.cwiseProduct(b1row.col(2)) + a32.cwiseProduct(b2row.col(2))), (a31.cwiseProduct(b1row.col(3)) + a32.cwiseProduct(b2row.col(3)));
	MatrixXd c3row = aux1.colwise().sum();
	MatrixXd C(4,4);
	C << 	c1row,
			c2row,
			c3row,
			MatrixXd::Zero(1,4);
	
	// % second part of Hessian
	VectorXd rho1 = -q1/nPoints * kappaM2.cwiseProduct(iEg.col(0));
	VectorXd rho2 = -q2/nPoints * kappaM2.cwiseProduct(iEg.col(1));
	MatrixXd Frow1 = kappaM1.cwiseProduct(lambda.col(0)) - kappaM2.cwiseProduct((lambda.col(2)).cwiseProduct(iEg.col(0)));
	MatrixXd Frow2 = kappaM1.cwiseProduct(lambda.col(1)) - kappaM2.cwiseProduct((lambda.col(2)).cwiseProduct(iEg.col(1)));
	MatrixXd G1row1 = (Frow1*Ones).cwiseProduct(iEg);
	MatrixXd G1row2 = (Frow2*Ones).cwiseProduct(iEg);
	MatrixXd G2row1 = ((z.col(0))*Ones).cwiseProduct(lambda);
	MatrixXd G2row2 = ((z.col(1))*Ones).cwiseProduct(lambda);
	MatrixXd Grow1 = G1row1 - G2row1;
	MatrixXd Grow2 = G1row2 - G2row2;
	MatrixXd h1row = (q1/nPoints * (kappaM1*Ones).cwiseProduct(Grow1)).colwise().sum();
	MatrixXd h2row = (q2/nPoints * (kappaM1*Ones).cwiseProduct(Grow2)).colwise().sum();
	MatrixXd aux2(nPoints,4);
	aux2 << rho1.cwiseProduct(Grow1.col(0)) + rho2.cwiseProduct(Grow2.col(0)), rho1.cwiseProduct(Grow1.col(1)) + rho2.cwiseProduct(Grow2.col(1)), rho1.cwiseProduct(Grow1.col(2)) + rho2.cwiseProduct(Grow2.col(2)), rho1.cwiseProduct(Grow1.col(3)) + rho2.cwiseProduct(Grow2.col(3));
	MatrixXd h3row = aux2.colwise().sum();
	MatrixXd H(4,4);
	H << 	h1row,
			h2row,
			h3row,
			MatrixXd::Zero(1,4);
			
	return C+H;
}