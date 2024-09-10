/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
KPP_REAL ros_ErrorNorm ( 
  /*~~~> Input arguments */  
     KPP_REAL Y[], KPP_REAL Ynew[], KPP_REAL Yerr[], 
     KPP_REAL AbsTol[], KPP_REAL RelTol[], 
     char VectorTol )
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Computes and returns the "scaled norm" of the error vector Yerr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   
{   	 
  /*~~~> Local variables */     
   KPP_REAL Err, Scale, Ymax;   
   int i;
   
   Err = ZERO;
   for (i=0; i<KPP_NVAR; i++) {
	Ymax = MAX(ABS(Y[i]),ABS(Ynew[i]));
     if (VectorTol) {
       Scale = AbsTol[i]+RelTol[i]*Ymax;
     } else {
       Scale = AbsTol[0]+RelTol[0]*Ymax;
     } /* end if */
     Err = Err+(Yerr[i]*Yerr[i])/(Scale*Scale);
   } /* for i */
   Err  = SQRT(Err/(KPP_REAL)KPP_NVAR);

   return Err;
   
} /* ros_ErrorNorm */