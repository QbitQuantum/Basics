/*--------------------------------------------*/
double K(double psi, double K_sat, double imp, double i, double s, double r, double a, double n, double m, double v, double pmin, double T)

{

	double TETA,psisat,K_unsat,iceratio;
	
	psisat=(pow((pow(1.0-i/(s-r),-1.0/m)-1.0),1.0/n))*(-1.0/a);
		
	if(psi>psisat) psi=psisat;
  
	TETA=1.0/pow((1.0+pow(a*(-Fmax(pmin,psi)),n)),m);
 
	if(T>=0){
		K_unsat=K_sat*(0.000158685828*T*T+0.025263459766*T+0.731495819);
	}else{
		K_unsat=K_sat*0.73;
	}
	
	K_unsat*=(pow(TETA,v))*(pow((1-pow((1-pow(TETA,(1.0/m))),m)),2.0));
	
	iceratio=i/(s-r);
	K_unsat*=(pow(10.0,-imp*iceratio));	
						
	return K_unsat;
 
}