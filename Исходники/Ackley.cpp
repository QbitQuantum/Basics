//
//  Function that calculates Ackley's function, for 2 variables, for specified x & y values
//
double Ackley::ack2Vars(double x, double y){
	double c1=20, c2=0.2, c3=2*PI;

	return -c1*exp(-c2*sqrt(0.5*(x*x + y*y))) - exp(0.5*(cos(c3*x)+cos(c3*y))) + c1 + 1;
}