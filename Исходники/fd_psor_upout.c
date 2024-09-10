static int Psor_UpOut(double s,NumFunc_1  *p,double l,double rebate,double t,double r,double divid,double sigma,int N,int M,double theta,double omega,double epsilon,double *ptprice,double *ptdelta)
{
  int      Index,PriceIndex,TimeIndex;
  int      j,loops;
  double   k,vv,loc,h,z,alpha,beta,gamma,y,alpha1,beta1,gamma1,up,upwind_alphacoef;
  double   error,norm,x;
  double   *P,*Obst,*Rhs;

  /*Memory Allocation*/
  P= malloc((N+2)*sizeof(double));
  if (P==NULL)
    return MEMORY_ALLOCATION_FAILURE;
  Obst= malloc((N+2)*sizeof(double));
  if (Obst==NULL)
    return MEMORY_ALLOCATION_FAILURE;
  Rhs= malloc((N+2)*sizeof(double));
  if (Rhs==NULL)
    return MEMORY_ALLOCATION_FAILURE;

  /*Time Step*/
  k=t/(double)M;

  /*Space Localisation*/
  vv=0.5*sigma*sigma;
  z=(r-divid)-vv;
  loc=sigma*sqrt(t)*sqrt(log(1.0/PRECISION))+fabs(z)*t;

  /*Space Step*/
  x=log(s);
  up=log(l);
  h=(up-(x-loc))/(double)(N+1);

  /*Coefficient of diffusion augmented*/
  if ((h*fabs(z))<=vv)
    upwind_alphacoef=0.5;
  else {
    if (z>0.) upwind_alphacoef=0.0;
    else  upwind_alphacoef=1.0;
  }
  vv-=z*h*(upwind_alphacoef-0.5);

  /*Lhs factor of theta-schema*/
  alpha=theta*k*(-vv/(h*h)+z/(2.0*h));
  beta=1.0+k*theta*(r+2.*vv/(h*h));
  gamma=k*theta*(-vv/(h*h)-z/(2.0*h));

  /*Rhs factor of theta-schema*/
  alpha1=k*(1.0-theta)*(vv/(h*h)-z/(2.0*h));
  beta1=1.0-k*(1.0-theta)*(r+2.*vv/(h*h));
  gamma1=k*(1.0-theta)*(vv/(h*h)+z/(2.0*h));


  /*Terminal Values*/
  for(PriceIndex=0;PriceIndex<=N;PriceIndex++) {
    Obst[PriceIndex]=(p->Compute)(p->Par,exp(x-loc+(double)PriceIndex*h));
    P[PriceIndex]= Obst[PriceIndex];
  }
  P[N+1]=rebate;

  /*Finite Difference Cycle*/
  for(TimeIndex=1;TimeIndex<=M;TimeIndex++)
    {
      /*Init Rhs*/
      for(j=1;j<=N;j++)
        Rhs[j]=P[j]*beta1+alpha1*P[j-1]+gamma1*P[j+1];

      /*Psor Cycle*/
      loops=0;
      do
        {
          error=0.;
          norm=0.;

          for(j=1;j<=N;j++)
            {
              y=(Rhs[j]-alpha*P[j-1]-gamma*P[j+1])/beta;
              y=MAX(Obst[j],P[j]+omega*(y-P[j]));

              error+=(double)(j+1)*fabs(y-P[j]);
              norm+=fabs(y);
              P[j]=y;
            }

          if (norm<1.0) norm=1.0;
          error=error/norm;

          loops++;
        }
      while ((error>epsilon) && (loops<MAXLOOPS));
    }
  Index=(int)floor(loc/h);

  *ptprice=P[Index]+(P[Index+1]-P[Index])*(exp(x)-exp(x-loc+Index*h))/(exp(x-loc+(Index+1)*h)-exp(x-loc+Index*h));

  /*Delta*/
  if(x==up)
    *ptdelta=(P[Index]-P[Index-1])/(s*h);
  else
    *ptdelta=(P[Index+1]-P[Index-1])/(2*s*h);

  /*Memory Desallocation*/
  free(P);
  free(Obst);
  free(Rhs);

  return OK;
}