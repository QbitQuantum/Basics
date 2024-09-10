void Tcanopy(long r, long c, double Tv0, double Tg, double Qg, double dQgdT, double Tg0, double Qg0, double Ta, double Qa, 
		double zmu, double zmT, double z0, double z0s, double d0, double z0r, double hveg, double v, double LR, double P, 
		double SW, double SWv, double LW, double e, double LSAI, double decaycoeff0, double *land, double Wcrn0, double Wcrnmax, 
		double Wcsn0, double Wcsnmax, double *dWcrn, double *dWcsn, double *LWv, double *LWg, double *Hv, double *Hg, 
		double *dHgdT, double *LEv, double *Eg, double *dEgdT, double *Ts, double *Qs, double *froot, double *theta, 
		DOUBLEVECTOR *soil_transp_layer, double *Lobukhov, PAR *par, long n, double *rh, double *rv, double *rc, double *rb, 
		double *r_uc, double *u_top, double *Etrans, double *Tv, double *Qv, double *decay, double *Locc,
		double *LWup_above_v, double psi, double **soil, double *T, DOUBLEVECTOR *soil_evap_layer){ 
	
	double C, C0;
	double A=1.0;
	double T00=Tv0, T10, T11=Tv0, T11p=Tv0, DT, Wcrn=Wcrn0, Wcsn=Wcsn0;
	double err0, err1=1.E+99, nw;
	double Lobukhov0, h0=0.0, h1, dhdT, dQ;
	double subl_can, melt_can, fwliq, fwice;
	double alpha, beta;
	long cont, cont2, chgsgn=0;
	short a=0;

	//vegetation thermal capacity
	//C0=0.02*LSAI*c_liq + c_ice*Wcsn + c_liq*Wcrn;
	C0=land[jcd]*LSAI*c_can + c_ice*Wcsn + c_liq*Wcrn;
	C=C0; 
	
	fwliq=pow(Wcrn/Wcrnmax,2./3.);
	fwice=pow(Wcsn/Wcsnmax,2./3.);	
		
	//calculates values at the instant t0 -> h0
	if(A<1){		
		*Ts=0.5*Tg0+0.5*Ta;
		*Qs=0.5*Qg0+0.5*Qa;		
		canopy_fluxes(r, c, T00, Tg0, Ta, Qg0, Qa, zmu, zmT, z0, z0s, d0, z0r, hveg, v, LR, P, SW, LW, e, LSAI, decaycoeff0, land,
					  Wcrn0, Wcrnmax, Wcsn0, Wcsnmax, &subl_can, Etrans, LWv, LWg, Hv, LEv, &h0, &dhdT, Ts, Qs, r_uc,  
					  froot, theta, soil_transp_layer, chgsgn, Lobukhov, par, n, rh, rv, rc, rb, u_top, decay, Locc, LWup_above_v,
					  psi, soil, &alpha, &beta, T, soil_evap_layer); 
	}

	//calculates values at the instant t1 -> h1, through iterations
	cont=0;
	chgsgn=0;	
	*Ts=0.5*Tg+0.5*Ta;
	*Qs=0.5*Qg+0.5*Qa;				
	canopy_fluxes(r, c, T11, Tg, Ta, Qg, Qa, zmu, zmT, z0, z0s, d0, z0r, hveg, v, LR, P, SW, LW, e, LSAI, decaycoeff0, land, Wcrn0, 
		Wcrnmax, Wcsn0, Wcsnmax, &subl_can, Etrans, LWv, LWg, Hv, LEv, &h1, &dhdT, Ts, Qs, r_uc, froot, theta, soil_transp_layer, chgsgn, 
		Lobukhov, par, n, rh, rv, rc, rb, u_top, decay, Locc, LWup_above_v, psi, soil, &alpha, &beta, T, soil_evap_layer); 
	
	melt_can = 0.0;
					
	do{

		T10=T11;
		
		//Generalized Newton-Raphson
		cont2=0;
		nw=1.0;
		err0=fabs( C*(T11-T00)/par->Dt - SWv - A*h1 - (1.-A)*h0 );
		
		//eq. C*(T11-T00)/Dt = cost + h(T10) + dh(T10)/dT * (T11-T10)
		//eq. C*(T11-T10)/Dt + C*(T10-T00)/Dt = cost + h(T10) + dh(T10)/dT * (T11-T10)
		//eq. T11-T10 = ( cost + h(T10) - C*(T10-T00)/Dt ) / ( C/Dt - dh/dT )
		
		DT=( -C*(T10-T00)/par->Dt + SWv + A*h1 + (1.0-A)*h0 ) / ( C/par->Dt - A*dhdT );
		
		if(DT!=DT) printf("ERROR NwRph Tcanopy T00:%f T10:%f SWv:%f h0:%f h1:%f dhdT:%f C:%f Wcsn:%f Wcrn:%f %ld %ld\n",
			T00,T10,SWv,h0,h1,dhdT,C,Wcsn,Wcrn,r,c); 
				
		Lobukhov0=(*Lobukhov);
		
		do{
			
			T11 = T10 + nw*DT;	
			
			if(subl_can<0 && T11<0){ //condensation as frost
				Wcsn=Wcsn0-subl_can*par->Dt;
				Wcrn=Wcrn0;
				
			}else if(subl_can<0 && T11>=0){ //condensation as dew
				Wcrn=Wcrn0-subl_can*par->Dt;
				Wcsn=Wcsn0;
				
			}else{	//partly evaporation, partly sublimation
				if(fwliq+fwice>0){
					Wcsn=Wcsn0-(fwice/(fwliq+fwice))*subl_can*par->Dt;
					Wcrn=Wcrn0-(fwliq/(fwliq+fwice))*subl_can*par->Dt;				
				}else{
					Wcsn=Wcsn0;
					Wcrn=Wcrn0;
				}
			}
						
			if(Wcrn>Wcrnmax) Wcrn=Wcrnmax;
			if(Wcrn<0) Wcrn=0.0;
			if(Wcsn>Wcsnmax) Wcsn=Wcsnmax;
			if(Wcsn<0) Wcsn=0.0;			
						
			if(T11>0 && Wcsn>0){	//melting
				melt_can=Fmin(Wcsn, c_ice*Wcsn*(T11-0.0)/Lf);
				T11p=T11 - Lf*melt_can/C;
				Wcsn-=melt_can;
				Wcrn+=melt_can;
				
			}else if(T11<0 && Wcrn>0){  //freezing
				melt_can=-Fmin(Wcrn, c_liq*Wcrn*(0.0-T11)/Lf);
				T11p=T11 - Lf*melt_can/C;
				Wcsn-=melt_can;
				Wcrn+=melt_can;	
				
			}else{
				melt_can=0.0;
				T11p=T11;
			}
									
			C=land[jcd]*LSAI*c_can + c_ice*Wcsn + c_liq*Wcrn;
			C=(C+C0)/2.;
			
			canopy_fluxes(r, c, T11p, Tg, Ta, Qg, Qa, zmu, zmT, z0, z0s, d0, z0r, hveg, v, LR, P, SW, LW, e, LSAI, decaycoeff0, 
						  land, Wcrn, Wcrnmax, Wcsn, Wcsnmax, &subl_can, Etrans, LWv, LWg, Hv, LEv, &h1, &dhdT, Ts, Qs, r_uc, 
						  froot, theta, soil_transp_layer, chgsgn, Lobukhov, par, n, rh, rv, rc, rb, u_top, decay, Locc,
						  LWup_above_v, psi, soil, &alpha, &beta, T, soil_evap_layer); 
			
			err1=fabs(C*(T11-T00)/par->Dt - SWv - A*h1 - (1.0-A)*h0 );
			
			nw/=3.0;
			cont2++;
																	
		}while(err1>err0 && cont2<5);	
		
		if(Lobukhov0*(*Lobukhov)<0) chgsgn++;		
				
		cont++;		
		
		if(fabs(T11-T10)<0.01 && err1<0.1) a=1;
								
	}while(a==0 && cont<par->maxiter_canopy);
	
	/*if(fabs(T11-T10)>0.5){
		printf("Tcanopy not converging %f %f %ld %ld \n",T10,T11,r,c);
	}*/
		
	*Tv=T11p;
	*dWcrn=Wcrn-Wcrn0;
	*dWcsn=Wcsn-Wcsn0;
			
	sat_spec_humidity(Qv, &dQ, 1.0, *Tv, P);
			
	turbulent_fluxes(*r_uc, *r_uc/beta, P, *Ts , Tg, *Qs, alpha*Qg, alpha*dQgdT, Hg, dHgdT, Eg, dEgdT);
		
	if(*Tv!=(*Tv)) printf("Tv no value %ld %ld\n",r,c);
			
}		