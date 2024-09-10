void cholesky_downdate (Eigen::Matrix<double, N, N>& L, Eigen::Matrix<double, N, 1> p) {

	L.template triangularView<Eigen::Lower>().solveInPlace(p);

	assert(p.squaredNorm() < 1); // otherwise the downdate would destroy positive definiteness.
	double rho = std::sqrt (1 - p.squaredNorm());

	Eigen::JacobiRotation<double> rot;
	Eigen::Matrix<double, N, 1> temp;
	temp.setZero();

	for (int i = N-1; i >= 0; --i) {
		rot.makeGivens(rho, p(i), &rho), p(i) = 0;
		apply_jacobi_rotation(temp, L.col(i), rot);
	}
}