	void gradient(View& view, const Eigen::VectorXd& parameters, Eigen::VectorXd& gradient_vector)
	{
		// TODO: Check concept for InputIterator

		//double N = std::distance(first_input, last_input);
		double scaling_factor = 1. / view.size();
		gradient_vector.setZero();

		// DEBUG
		//std::cout << gradient_ << std::endl;

		for (unsigned int i = 0; i < view.size(); i++) {
			forward_propagation(parameters, view.first(i), outputs());
			back_propagation_error(parameters, view.first(i), outputs(), view.second(i), gradient_vector, scaling_factor);
		}

		// DEBUG
		//std::cout << gradient_ << std::endl;
	}