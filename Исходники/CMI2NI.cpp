double cas(const MatrixXd & x, const MatrixXd &y, const MatrixXd & z)
{
	int n1 = z.rows();
	int n = n1 + 2;
	MatrixXd xz(x.rows() + z.rows(), x.cols());
	xz << x, z;
	MatrixXd xyz(x.rows() + y.rows() + z.rows(), x.cols());
	xyz << x, y, z;

	MatrixXd Cov = Covar(x.transpose());
	MatrixXd Covm = Covar(xyz.transpose());
	MatrixXd Covm1 = Covar(xz.transpose());
	MatrixXd InvCov = Cov.inverse();
	MatrixXd InvCovm = Covm.inverse();
	MatrixXd InvCovm1 = Covm1.inverse();

	MatrixXd C11(1, 1); C11(0, 0) = InvCovm1(0, 0);
	MatrixXd C12(1, 1); C12 = MatrixXd::Zero(1, 1);
	MatrixXd C13 = InvCovm1.block(0, 1, 1, n1);
	MatrixXd C23 = InvCovm.block(1, 2, 1, n1) -
		InvCovm(0, 1) * (1.0 / (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0)))*(InvCovm.block(0, 2, 1, n1) - InvCovm1.block(0, 1, 1, n1));
	MatrixXd C22(1, 1);
	C22(0, 0) = InvCovm(1, 1) - InvCovm(0, 1)*InvCovm(0, 1)*(1.0 / (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0)));
	MatrixXd C33 = InvCovm.block(2, 2, n1, n1) - (1.0 / (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0)))*
		((InvCovm.block(0, 2, 1, n1) - InvCovm1.block(0, 1, 1, n1)).transpose() *  (InvCovm.block(0, 2, 1, n1) - InvCovm1.block(0, 1, 1, n1)));

	MatrixXd C1(1, n); C1 << C11, C12, C13;
	MatrixXd C2(1, n); C2 << C12, C22, C23;
	MatrixXd C3(n1, n); C3 << C13.transpose(), C23.transpose(), C33;

	MatrixXd InvC(n, n); InvC << C1, C2, C3;

	double C0 = Cov(0, 0) * (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0));
	double CS = 0.5 * ((InvC*Covm).trace() + log(C0) - n);
	return CS;
}