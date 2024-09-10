int main( int argc, char *argv[] )
{
	/* parameters of strings */
	double Gamma   = LOOP_RAD_POWER;	/* power radiated by loops */
	double c       = CUSPS_PER_LOOP;	/* cusps per loop */

	double p,epsilon,f,Gmu,alpha;
	double gammaAverage = 0, gammaMin = 0, gammaMax =0;
	char filename[FILENAME_MAX];
	FILE *fp;
	int i,j,k,l;

	/* read the command line */
	if (ReadCommandLine(argc,argv,&CLA)) return 1;
	f=CLA.f;

	/* read efficiency function */
	if (ReadEfficiencyFile(CLA)) return 2;
	
	snprintf( filename, sizeof( filename ), "gamma.dat");
	fp = fopen( filename, "w" );
	fprintf( fp,"%%     p           n           epsilon         Gmu       gammaAverage    gammaMin      gammaMax\n");
	for ( i = 0; i <  CLA.nepsilon; i++ )
	  {
	    epsilon=pow(10.0,CLA.logepsilonstart+i*(CLA.logepsilonend-CLA.logepsilonstart)/(CLA.nepsilon-1));
	    
	    for ( j = 0; j <  CLA.nGmu; j++ )
	      {
		Gmu=pow(10.0,CLA.logGmustart+j*(CLA.logGmuend-CLA.logGmustart)/(CLA.nGmu-1));
		alpha = epsilon * pow( Gamma * Gmu, CLA.n );
			       
		/* find the z's corresponding to those A's */
		if(findzofA(Gmu, alpha)) return 3;
		
		/* compute the rate derivative at those z's */
		if(finddRdz(Gmu, alpha, f, Gamma)) return 4;
			
		for ( k = 0; k <  CLA.np; k++ )
		  {
		    p=pow(10.0, CLA.logpstart+k*(CLA.logpend-CLA.logpstart)/(CLA.np));
		    
 		    fprintf(stdout,"%%Computing effective rate for Gmu=%e, epsilon=%e, p=%e\n ",Gmu, epsilon, p);
		    
		    /* Compute the rate of bursts */
		    gammaAverage=0.0;
		    gammaMin = 0.0;
		    gammaMax = 0.0;
		    for (l = 0; l < Namp-1; l++)
		      {
			Dlnz = (-log(zofA[l+1])+log(zofA[l]));
			gammaAverage += eff[l] * zofA[l] * dRdz[l] * Dlnz;
			gammaMin += fmaxf((eff[l]-Deff[l]),0.0) * zofA[l] * dRdz[l] * Dlnz;
			gammaMax += fminf((eff[l]+Deff[l]),1.0) * zofA[l] * dRdz[l] * Dlnz;
		      }
		    gammaAverage *= c/p;
		    gammaMin *= c/p;
		    gammaMax *= c/p;

		    fprintf( fp,"%e  %e  %e  %e  %e  %e  %e\n", p,CLA.n,epsilon,Gmu,gammaAverage,gammaMin,gammaMax);

		  }
				
	      }
	  }

	fclose( fp );

	free(amp);
	free(lnamp);
	free(eff);
	free(Deff);
	free(zofA);
	free(dzdA);
	free(dRdz);

	return 0;
}