	/**
	 * \brief add a point
	 */
	void	addPoint(const FocusPoint& point,
			const Ice::Current& /* current */) {
		std::cout << timeformat("%H:%M:%S ", time(NULL));
		std::cout << point.position << ": " << point.value;
		std::cout << std::endl;
	}