static Vector_3 leastSquaresPoint(const std::vector<unsigned> activeGroup,
		const std::vector<SupportItem> &items)
{
	DEBUG_START;
	Eigen::Matrix3d matrix;
	Eigen::Vector3d vector;
	for (unsigned i = 0; i < 3; ++i)
	{
		vector(i) = 0.;
		for (unsigned j = 0; j < 3; ++j)
			matrix(i, j) = 0.;
	}

	std::cout << "Calculating least squares points for the following items"
		<< std::endl;
	for (unsigned iPlane : activeGroup)
	{
		SupportItem item = items[iPlane];
		Vector_3 u = item.direction;
		double value = item.value;
		std::cout << "  Item #" << iPlane << ": u = " << u << "; h = "
			<< value << std::endl;
		for (unsigned i = 0; i < 3; ++i)
		{
			for (unsigned j = 0; j < 3; ++j)
				matrix(i, j) += u.cartesian(i)
					* u.cartesian(j);
			vector(i) += u.cartesian(i) * value;
		}
	}
	Eigen::Vector3d solution = matrix.inverse() * vector;

	Vector_3 result(solution(0), solution(1), solution(2));
	std::cout << "Result: " << result << std::endl;
	for (unsigned iPlane : activeGroup)
	{
		SupportItem item = items[iPlane];
		double delta = item.direction * result - item.value;
		std::cout << "  delta = " << delta << std::endl;
	}
	DEBUG_END;
	return result;
}