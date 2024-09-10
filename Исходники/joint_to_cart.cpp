// Convert joint torques to end effector force/torque
void computeFT(Eigen::VectorXd& ee_ft) {
	Eigen::MatrixXd jac;
	mRobot->getJacobian(jac);
	Eigen::MatrixXd trans = jac*jac.transpose() + singular_tol*Eigen::MatrixXd::Identity(jac.rows(), jac.rows());
	// f = inv(J*J')*J*tau
	ee_ft = (trans.inverse()*jac)*read_torque;
}