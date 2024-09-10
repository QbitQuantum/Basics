void up_rk4_abm(VectorXd &F_Eingang, double h, MatrixXd &Y, M_struct &M1, int j) {

	double F;
	double F_grad;
	F = F_Eingang(1);
	F_grad = F_Eingang(2);

	MatrixXd dy1;
	MatrixXd dy2;
	MatrixXd dy3;
	MatrixXd dy4;
	

	MatrixXd Y2;
	MatrixXd Y3;
	MatrixXd Y4;
	
	double F2;
	double F3;
	double F4;
	
	MatrixXd Y1(4 * (n+1), 2);
	Y1 = Y.block(0, 0, 4 * (n + 1), j * 2);
	dy1 = up_ode(Y1, F, M1);

	std::cout << dy1 << std::endl << std::endl << std::endl << Y1;

	Y2 = Y1 + dy1;
	F2 = (F + F_grad * h / 2);
	dy2 = h * up_ode(Y2, F2, M1);

	Y3 = Y1 + dy2 / 2;
	F3 = (F + F_grad * h / 2);
	dy3 = h * up_ode(Y3, F, M1);

	Y4 = Y1 + dy3;
	F2 = (F + F_grad * h);
	dy4 = h * up_ode(Y4, F, M1);

	Y.block(0, j*2, 4 * (n + 1), 2) = Y1 + h / 6 * (dy1 + 2 * dy2 + 3 * dy3 + dy4);



//	std::cout << dy << std::endl << std::endl << std::endl;
}