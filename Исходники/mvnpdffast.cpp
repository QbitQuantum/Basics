template<int N> void calculateGaussPdf(Eigen::Matrix<double,Eigen::Dynamic,N> X, Eigen::Matrix<double,1,N> mu, Eigen::Matrix<double,N,N> C, double* result){
    Eigen::Matrix<double,N,N> L = C.llt().matrixL().transpose(); // cholesky decomposition
    Eigen::Matrix<double,N,N> Linv = L.inverse();
    
    double det = L.diagonal().prod(); //determinant of L is equal to square rooot of determinant of C
	double lognormconst = -log(2 * M_PI)*X.cols()/2 - log(fabs(det));

    Eigen::Matrix<double,1,N> x = mu;
    Eigen::Matrix<double,1,N> tmp = x;
    for (int i=0; i<X.rows(); i++){
        x.noalias() = X.row(i) - mu;
        tmp.noalias() = x*Linv;
        double exponent = -0.5 * (tmp.cwiseProduct(tmp)).sum();
        result[i] = lognormconst+exponent;
    }
    
    /*
	Eigen::Matrix<double,Eigen::Dynamic,N> X0 = (X.rowwise() - mu)*Linv;
	Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,1> > resultMap(result, X.rows());
	resultMap = (X0.rowwise().squaredNorm()).array() * (-0.5) + lognormconst;
    */
    
    fmath::expd_v(result, X.rows());
}