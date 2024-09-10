inline Real evaluate_point<1>(const Triangle<3>& t, const Point& point, const Eigen::Matrix<Real,3,1>& coefficients)
{
	Eigen::Matrix<Real,3,1> bary_coeff = t.getBaryCoordinates(point);
	//std::cout<< "B-coord: "<<bary_coeff<<std::endl;

	return(coefficients.dot(bary_coeff));
}