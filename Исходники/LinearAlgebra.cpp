Eigen::Matrix3d LinearAlgebra::invMatrixM(const Eigen::Matrix3d& M) {
	Eigen::Matrix3d result;

	// TODO: return the inverse of matrix M
	result = M.inverse();

	return result;
}