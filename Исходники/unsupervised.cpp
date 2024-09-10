double unsupervised::gaussian(const ColumnVector& ob, const ColumnVector& mix_mu, const Matrix& mix_sigma){
	ColumnVector tmp(Dim);
	tmp = ob-mix_mu;
	double x = (tmp.t() * mix_sigma.i() * tmp).AsScalar();
	if(x<0.0) x = 0.0; //for avoiding the failure from calculation error of newmat library.
    
	tmp.CleanUp();
	return (exp(x*(-0.5)) / (pow(2.0*M_PI,ob.Nrows()*0.5)*pow(mix_sigma.Determinant(),0.5)));
}