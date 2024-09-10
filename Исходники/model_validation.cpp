double* simulatePlant(double *state_vect, double *input_vect, double *state_op_vect, double sampling_time)
{
	double input_op_vect[4] = {0.0, 0.0, 0.0, 0.0};
	Eigen::Map<Eigen::VectorXd> x(state_vect, num_states_);
	Eigen::Map<Eigen::VectorXd> x_bar(state_op_vect, num_states_);
	Eigen::Map<Eigen::VectorXd> u(input_vect, num_inputs_);
	Eigen::Map<Eigen::VectorXd> u_bar(&input_op_vect[0], num_inputs_);
	
	Eigen::MatrixXd A = Eigen::MatrixXd::Identity(num_states_, num_states_);
	Eigen::MatrixXd B = Eigen::MatrixXd::Zero(num_states_, num_inputs_);
	
	Eigen::MatrixXd M = Eigen::MatrixXd::Zero(num_inputs_, num_inputs_);
	Eigen::VectorXd f_bar = Eigen::MatrixXd::Zero(num_inputs_, 1);
	
	double phi = x_bar(6);
	double theta = x_bar(7);
	double p = x_bar(9);
	double q = x_bar(10);
	double r = x_bar(11);
	
	M << 1., 1., 1., 1., 0., -1., 0., 1., 1., 0., -1., 0., -1., 1., -1., 1.;
	f_bar(0) = g_ * m_ / (Ct_ * cos(phi) * cos(theta));
	f_bar(1) = (Izz_ - Iyy_) * q * r / (Ct_ * d_);
	f_bar(2) = (Izz_ - Ixx_) * p * r / (Ct_ * d_);
	f_bar(3) = (Iyy_ - Ixx_) * p * q / Cq_;
	u_bar = M.inverse() * f_bar;
	u_bar = u_bar.cwiseSqrt();
	
	// Compute the matrices of the linear dynamic model	
	computeLTIModel(A, B, state_op_vect, input_op_vect);
	
	x = x_bar + A * (x - x_bar) + B * (u - u_bar);
		
	return state_vect;
}