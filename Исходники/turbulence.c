void turbulent_fluxes(double rh, double rv, double P, double Ta, double T, double Qa, double Q, double dQdT, 
					  double *H, double *dHdT, double *E, double *dEdT){

	double rho, cp, pot;
	
	rho=air_density(0.5*(Ta+T), Qa, P);
	cp=air_cp(0.5*(Ta+T));
	
	//pot=pow((1000.0/P),(0.286*(1-0.23*Qa)));
	pot=1.0;
	
	//sensible heat flux [W/m2] 
	/*a maximum value of the resistance for the sensible heat flux was introduced according to Jordan et el., 1999
	(HEAT BUDGET OF SNOW-COVERED SEA ICE AT NORTH POLE 4) as Cwindless=0.5 W m^2 K^-1, rh=rho*cp/C=1300/0.5=2600*/
	*H=cp*rho*pot*(T-Ta)/Fmin(rh,2.6E3);	
	*dHdT=cp*rho*pot/Fmin(rh,2.6E3);	
	//*H=cp*rho*pot*(T-Ta)/rh;	
	//*dHdT=cp*rho*pot/rh;		
	
	//evaporation [kg/(s*m2)]
	*E=rho*(Q-Qa)/rv;	
	*dEdT=rho*dQdT/rv;

}