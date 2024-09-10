mathtools::geometry::euclidian::HyperEllipse<2> skeleton::model::Perspective::toObj(
		const Eigen::Matrix<double,skeleton::model::meta<skeleton::model::Projective>::stordim,1> &vec,
		const mathtools::geometry::euclidian::HyperEllipse<2> &) const
{
	double z = 1.0/(sqrt(vec(0)*vec(0) + vec(1)*vec(1) + 1.0 - vec(2)*vec(2)));
	double x = vec(0) * z;
	double y = vec(1) * z;
	
	Eigen::Matrix2d mat;
	mat << 1.0-x*x , -x*y    ,
		   -x*y    , 1.0-y*y ;
	
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> solv(mat);
	
	Eigen::Matrix2d axes = Eigen::Matrix2d::Identity();
	double fac = Eigen::Vector2d(-x*z,-y*z).transpose()*mat.inverse()*Eigen::Vector2d(-x*z,-y*z) - 1.0 + z*z;
	axes = solv.eigenvectors()*Eigen::DiagonalMatrix<double,2>(Eigen::Vector2d(sqrt(fac/solv.eigenvalues()(0)),sqrt(fac/solv.eigenvalues()(1))));
	
	mathtools::affine::Point<2> pt(vec(0),vec(1),m_frame2);
	return mathtools::geometry::euclidian::HyperEllipse<2>(pt,m_frame2->getBasis()->getMatrix()*axes);
}