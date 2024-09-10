double complex secondPart(const int l, const double gamma, const double Lamda, const double qSqur, int * const rstatus)
{
  int s1 = 0, s2 = 0;
  double complex secondPartInt = 0+0*I;
  if(l != 0){
    secondPartInt = 0.0;
  }
  else{
    //Integration method.
    /*
      secondPartInt = spheHarm(0, 0, 0, 0, &s1) * gamma * pow(M_PI,3.0/2.0) 
      * ( 2 * qSqur * sndInteFunc(Lamda, qSqur, &s2)
      -2 * exp(Lamda * qSqur)/sqrt(Lamda));
    */
    //Arithmetic method.
    double inteCore = 0.0;
    if(qSqur > 0){
      //Dawson function for qSqur>0
      inteCore = 4 * sqrt(qSqur) * exp(Lamda * qSqur) * gsl_sf_dawson(sqrt(Lamda * qSqur)); 
    }
    else if(fabs(qSqur) < DBL_EPSILON) {
      inteCore = 0;
    }
    else if(qSqur < 0){
      //Error function for qSqur<0
      inteCore = -2 * sqrt(M_PI) * sqrt( - qSqur) * erf( sqrt( - Lamda * qSqur) );
    }
    
    secondPartInt = spheHarm(0, 0, 0, 0, &s1) * gamma * pow(M_PI,3.0/2.0)
      * ( inteCore 	-  2 * exp(Lamda * qSqur)/sqrt(Lamda));
  }
  *rstatus = s1 + s2;
  //printf("Lamda=%lf,qSqur = %.4f\nsecondPartInt = %.24f \n", Lamda, qSqur, secondPartInt);
  return secondPartInt;
}