typename PointMatcher<T>::TransformationParameters TransformationsImpl<T>::RigidTransformation::correctParameters(const TransformationParameters& parameters) const
{
	TransformationParameters ortho = parameters;
	if(ortho.cols() == 4)
	{
		const Eigen::Matrix<T, 3, 1> col0 = parameters.block(0, 0, 3, 1).normalized();
		const Eigen::Matrix<T, 3, 1> col1 = parameters.block(0, 1, 3, 1).normalized();
		const Eigen::Matrix<T, 3, 1> col2 = parameters.block(0, 2, 3, 1).normalized();


		ortho.block(0, 0, 3, 1) = col1.cross(col2);
		ortho.block(0, 1, 3, 1) = col2.cross(col0);
		ortho.block(0, 2, 3, 1) = col2;
	}
	else if(ortho.cols() == 3)
	{
		// R = [ a b]
		//     [-b a]
		
		// mean of a and b
		T a = (parameters(0,0) + parameters(1,1))/2; 	
		T b = (-parameters(1,0) + parameters(0,1))/2;
		T sum = sqrt(pow(a,2) + pow(b,2));

		a = a/sum;
		b = b/sum;

		ortho(0,0) =  a; ortho(0,1) = b;
		ortho(1,0) = -b; ortho(1,1) = a;
	}


	return ortho;
}