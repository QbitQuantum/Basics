// This needs to update every time we find a new goal
void update_C_ellipse_Matrix() {
	int d = setup_values.dimension;
	VectorXd goal_state = goal_node->state;

	// SVD stuff for ball
	VectorXd a1 = goal_state - setup_values.initial_state;
	MatrixXd M(d, d);
	M.setZero(d,d);
	M.col(0) = a1;

	// Perform SVD on M
	MatrixXd U = M.jacobiSvd(ComputeFullU | ComputeFullV).matrixU();
	MatrixXd V = M.jacobiSvd(ComputeFullU | ComputeFullV).matrixV();

	// Create W matrix
	MatrixXd W(d, d);
	W.setZero(d,d);
	for(int i = 0; i < d; ++i) {
		if (i == d - 1) {
			W(i, i) = U.determinant() * V.determinant();
		} else {
			W(i, i) = 1;
		}
	}

	// Multiply to update C matrix
	C_ellipse = U * W * V.transpose();

}