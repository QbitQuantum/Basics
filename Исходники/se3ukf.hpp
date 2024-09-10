	void print_if_too_large(const Vector3 & update, const std::string & name) {
		if (update.array().abs().maxCoeff() > M_PI / 4) {
			std::cout << "[" << iteration << "]" << name
					<< " has too large elements " << std::endl
					<< update.transpose() << std::endl;
		}
	}