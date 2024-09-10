//params is a matrix of nx2 where n is the number of landmarks
//for each landmark, the x and y pose of where it is
//pose is a matrix of 2x1 containing the initial guess of the robot pose
//delta is a matrix of 2x1 returns the increment in the x and y of the robot
void LMAlgr::computeIncrement(Eigen::MatrixXf params, Eigen::MatrixXf pose, double lambda, Eigen::MatrixXf error, Eigen::MatrixXf &delta){
	Eigen::MatrixXf Jac;
	Jac.resize(params.rows(), 2);
	//initialize the jacobian matrix
	for(int i = 0; i < params.rows(); i++){
		Jac(i, 0) = (params(i, 1) - pose(1, 0)) / (pow(params(i, 0) - pose(0, 0), 2) + pow(params(i, 1) - pose(1, 0), 2));
		Jac(i, 1) = -1 * (params(i, 0) - pose(0, 0)) / (pow(params(i, 0) - pose(0, 0), 2) + pow(params(i, 1) - pose(1, 0), 2));
	}
	Eigen::MatrixXf I;
	I = Eigen::MatrixXf::Identity(2, 2);
	Eigen::MatrixXf tmp = (Jac.transpose() * Jac) + (lambda * I);
	Eigen::MatrixXf incr = tmp.inverse() * Jac.transpose() * error;
	delta = incr;
}