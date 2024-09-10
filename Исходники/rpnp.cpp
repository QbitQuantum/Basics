void mrpt::vision::pnp::rpnp::calcampose(Eigen::MatrixXd& XXc, Eigen::MatrixXd& XXw, Eigen::Matrix3d& R2, Eigen::Vector3d& t2)
{
	Eigen::MatrixXd X = XXc;
	Eigen::MatrixXd Y = XXw;
	Eigen::MatrixXd K = Eigen::MatrixXd::Identity(n, n) - Eigen::MatrixXd::Ones(n, n) * 1 / n;
	Eigen::VectorXd ux, uy;
	uy = X.rowwise().mean();
	ux = Y.rowwise().mean();

	// Need to verify sigmax2
	double sigmax2 = (((X*K).array() * (X*K).array()).colwise().sum()).mean();

	Eigen::MatrixXd SXY = Y*K*(X.transpose()) / n;

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(SXY, Eigen::ComputeThinU | Eigen::ComputeThinV);

	Eigen::Matrix3d S = Eigen::MatrixXd::Identity(3, 3);
	if (SXY.determinant() <0)
		S(2, 2) = -1;

	R2 = svd.matrixV()*S*svd.matrixU().transpose();

	double c2 = (svd.singularValues().asDiagonal()*S).trace() / sigmax2;
	t2 = uy - c2*R2*ux;
	 
	Eigen::Vector3d x, y, z;
	x = R2.col(0);
	y = R2.col(1);
	z = R2.col(2);

	if ((x.cross(y) - z).norm()>0.02)
		R2.col(2) = -R2.col(2);
}