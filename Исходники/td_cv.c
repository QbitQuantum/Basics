double nie_alphas(double x1,double x2,double re0,double rcore,double qe) {
	double res0;
    res0 = re0/sqrt(1-qe*qe);

	double al1,al2;
    al1 = atan(x1*sqrt(1-qe*qe)/(hfunc(x1,x2,rcore,qe)+rcore));
    al2 = atanh(x2*sqrt(1-qe*qe)/(hfunc(x1,x2,rcore,qe)+rcore*qe*qe));
    return res0*al1*res0*al2;
}