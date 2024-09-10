//We find in an  authomatic way the extremes of integration
int findlowuplimit(int model,  double rf, double dt, int maxnummoments, 
				  int ndates, double lowfactor, double upfactor, 
				  double parameters[], double extremes[])
{
	int kk;
	double **momtable;
	double *moments;
	double *ArAvmoments;
	double mu1,mu2,mom1,mom2;
	double levylow,levyup, lowlim;
    double uplim;
	double bound;
    
    ArAvmoments = dvector(1, 5);
    momtable = dmatrix(1, ndates, 1, maxnummoments);
    moments = dvector(1, maxnummoments);
//vectors where to store the outputs of the FFT inversion
	
  
//compute the moments of the arithmetic average
	newmomentsAM(model, rf, dt, maxnummoments, ndates, parameters, momtable);
    
	for(kk=1;kk<maxnummoments+1;kk++)
      {moments[kk]=momtable[ndates][kk];
      }
	mu1=momtable[ndates][1];
	mu2=momtable[ndates][2];
    //	printf("\nMOMENTS SUM\nm1=%.12f m2=%.12f\n", mu1,mu2);

	uplim=log(mu1+upfactor*POW(mu2-mu1*mu1,0.5));
	bound=boundAM(model, uplim, rf, dt, maxnummoments, ndates, parameters, moments);

   
	while(bound>POW(10.0,-5.0)) 
	{
		uplim=uplim+0.15;
		bound=boundAM(model, uplim, rf, dt, maxnummoments, ndates, parameters, moments);
	//	printf("test: low%.12f\t up %.12f \tbound %.15f\n",lowlim,uplim,bound);
	}	
   
	mom1=MomentsLevy(model, rf, 1, dt, parameters);
	mom2=MomentsLevy(model, rf, 2, dt, parameters);
	//printf("\nMOMENTS Levy\nm1=%.12f m2=%.12f\n",
	//mom1,mom2);
    
	levylow=mom1-lowfactor*POW(mom2-mom1*mom1,0.5);
    bound=BoundLowerTailLevy(model, -levylow, rf, dt, maxnummoments, parameters);
    
	while(bound>POW(10.0,-8.0)) 
	{
		levylow=levylow-0.05;

		bound=BoundLowerTailLevy(model, -levylow, rf, dt, maxnummoments, parameters);
	}

   
	levyup=mom1+lowfactor*POW(mom2-mom1*mom1,0.5);
    bound=BoundUpperTailLevy(model, levyup, rf, dt, maxnummoments, parameters);

	while(bound>POW(10.0,-8.0)) 
	{
		levyup=levyup+0.05;

		bound=BoundUpperTailLevy(model, levyup, rf, dt, maxnummoments, parameters);
	
	}
	
	lowlim=-MAX(fabs(levylow),levyup);
	//impliedfactor=(mom1-lowlim)/POW(mom2-mom1*mom1,0.5);

	extremes[1]=lowlim;
	extremes[2]=uplim;

    free_dvector(moments,1,maxnummoments);
    free_dvector(ArAvmoments,1,5);
    free_dmatrix(momtable,1, ndates, 1, maxnummoments);

    return 1;
}