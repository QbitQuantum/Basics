int evaluate_integral(double R, double beta, double gamma, double a_dm, double a_s, double M_dm, double M_s, double *sig_p, double *R_arcmin)
{
  
  int Nint = 10000;    // NUMBER OF INTERVALS
  double result, error, s, aux, X_s, I_R;
  
  gsl_integration_workspace *z = gsl_integration_workspace_alloc(Nint);
  gsl_function F1;
  
  struct param params;
  
  params.beta  =  beta;
  params.a_s   =  a_s;
  params.a_dm  =  a_dm;
  params.M_s   =  M_s;
  params.M_dm  =  M_dm;       
  params.R     =  R;

  //////////////////////////////////////////////////////////////
  //  THIS IS JUST TO PRINT THE INTEGRAND TO SEE ITS BEHAVIOR  //
  ///////////////////////////////////////////////////////////////
  /* 
    {
    FILE *pf=NULL;
    double r;
    pf=fopen("puto_archivo.dat","w");
    for(r=0; r<LIMIT_RADIUS; r=r+1)
    {
    fprintf(pf,"%16.8e %16.8e\n",r, integrando(r, &params));
    }
    fclose(pf);
    exit(0);
    } 
  */
  ///////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  
  F1.function = &integrando;
  F1.params = &params;
  
  //gsl_integration_qags(&F1, R, LIMIT_RADIUS, 1.0e-8, 1e-6, Nint, z, &result, &error); 
  gsl_integration_qag(&F1, R, LIMIT_RADIUS, 1.0e-5, 1e-5, Nint, 1, z, &result, &error); 
  //printf("R = %lf I=%lf\n",R, result);
  
  s = R/a_s;
  
  if (s < (1.0-ZERO))
    { 
      aux = 1.0 - s*s;
      X_s = (1.0 / sqrt(aux)) * log((1.0 + sqrt(aux))/s);
      I_R = (M_s/(2.0*M_PI*a_s*a_s*gamma*aux*aux))*( (2.0+s*s)*X_s - 3.0 );
    }
  
  if(s >= (1.0-ZERO) && s <= (1.0+ZERO) )
    {
      X_s = 1.0;
      I_R = (2.0*M_s)/(15.0*M_PI*a_s*a_s*gamma);
    }
  
  if (s > (1.0 + ZERO))
    {
      X_s = (1.0 / sqrt(s*s - 1)) * acos(1.0/s);
      I_R = (M_s/(2.0*M_PI*a_s*a_s*gamma*(1.0-s*s)*(1.0-s*s)))*((2.0+s*s)*X_s - 3.0);
    }      
  
  *sig_p = sqrt( (G*result) / (gamma*I_R*M_PI) ) ;
  
  //THIS LINE CONVERTS FROM PARSECS TO ARCMIN SINCE THE OBSERVATIONAL DATA IS IN THOSE UNITS
  *R_arcmin = R*3437.75/DISTANCE;
  
  gsl_integration_workspace_free(z);
  
  return 0;  
}