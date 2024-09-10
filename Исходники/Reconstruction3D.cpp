Eigen::Matrix3d Reconstruction3D::computeEpipoleMat(const Eigen::Matrix3d& F)
{
	Eigen::JacobiSVD<Eigen::MatrixXd> svd(F.transpose(), Eigen::ComputeFullV);
	Eigen::MatrixXd kernel = svd.matrixV().col(svd.matrixV().cols() - 1);

	Eigen::Matrix3d e(3, 3);
	e(0, 0) = kernel(0);
	e(0, 1) = kernel(1);
	e(0, 2) = kernel(2);
	e(1, 0) = kernel(3);
	e(1, 1) = kernel(4);
	e(1, 2) = kernel(5);
	e(2, 0) = kernel(6);
	e(2, 1) = kernel(7);
	e(2, 2) = kernel(8);

	return e;
}