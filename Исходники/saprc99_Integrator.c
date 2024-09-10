/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
double ros_ErrorNorm ( 
  /*~~~> Input arguments */  
     volatile double Y[], double Ynew[], double Yerr[], 
     volatile double AbsTol[], volatile double RelTol[], 
     char VectorTol )
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Computes and returns the "scaled norm" of the error vector Yerr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   
{   	 
  /*~~~> Local variables */     
   double Err, Scale, Ymax;   
   int i;
   
   Err = ZERO;
   for (i=0; i<74; i++) {
	Ymax = MAX(ABS(Y[i]),ABS(Ynew[i]));
     if (VectorTol) {
       Scale = AbsTol[i]+RelTol[i]*Ymax;
     } else {
       Scale = AbsTol[0]+RelTol[0]*Ymax;
     } /* end if */
     Err = Err+(Yerr[i]*Yerr[i])/(Scale*Scale);
   } /* for i */
   Err  = SQRT(Err/(double)74);

   return Err;
   
} /* ros_ErrorNorm */