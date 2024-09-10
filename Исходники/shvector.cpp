Matrix3x3 SHVector::mu2() const {
	const Float sqrt5o3 = std::sqrt((Float) 5/ (Float) 3);
	const Float sqrto3 = std::sqrt((Float) 1/ (Float) 3);
	Matrix3x3 result;
	result.setZero();

	SAssert(m_bands > 0);
	result(0, 0) = result(1, 1) =
		result(2, 2) = sqrt5o3*operator()(0,0);

	if (m_bands >= 3) {
		result(0, 0) += -operator()(2,0)*sqrto3 + operator()(2,2);
		result(0, 1) = operator()(2,-2);
		result(0, 2) = -operator()(2, 1);
		result(1, 0) = operator()(2,-2);
		result(1, 1) += -operator()(2,0)*sqrto3 - operator()(2,2);
		result(1, 2) = -operator()(2,-1);
		result(2, 0) = -operator()(2, 1);
		result(2, 1) = -operator()(2,-1);
		result(2, 2) += 2*sqrto3*operator()(2,0);
	}

	return result * (2*std::sqrt((Float) M_PI / 15));
}