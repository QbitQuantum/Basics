/* ********************************************************************************************* */
void moveFoot(const Eigen::VectorXd& dx, bool left, Vector6d& dq) {

	// Get the jacobian
	Eigen::MatrixXd J = hubo->getBodyNode(left ? "leftFoot" : "rightFoot")
		->getWorldJacobian().bottomRightCorner<6,6>();
	Eigen::MatrixXd temp = J.topRightCorner<3,6>();
	J.topRightCorner<3,6>() = J.bottomRightCorner<3,6>();
	J.bottomRightCorner<3,6>() = temp;
	for(size_t i = 0; i < 6; i++) J(i,i) += 0.005;
	if(dbg) std::cout << "J= [\n" << J << "];\n";

	// Compute the inverse
	Eigen::MatrixXd JInv;
	JInv = J;
	aa_la_inv(6, JInv.data());

	// Compute joint space velocity
	if(dbg) cout << "dxRightLeg: " << dx.transpose() << endl;
	dq = (JInv * dx);
	if(dq.norm() > max_step_size) dq = dq.normalized() * max_step_size;
	if(dbg) cout << "dqRightLeg: " << dq.transpose() << endl;
}