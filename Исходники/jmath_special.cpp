//========================================================================
//========================================================================
//
//	NAME:	complex<double> bessel_2_complex(int n, complex<double> arg)
//
//	DESC:	Calculates the Bessel function of the second kind (Yn) for
//		complex arguments.
//
//	INPUT:
//		int n:: Order of Bessel function
//		complex<double> arg: Bessel function argument
//	
//	OUTPUT:
//		complex<double> Yn:: Bessel function of the second kind of
//			order n
//		
//	NOTES:	1) The Bessel function of the second kind is defined as:
//			Yn(x) = (2.0*Jn(x)/pi)*(ln(x/2) + gamma_e) 
//				+ sum{m=0, m=inf}[(((-1)^(m-1))*(hs(m) + 
//					hs(m+n)) + x^(2*m))/(((2.0^(2*m+n))*m!*(m+n)!)
//				- sum{m=0, m=(n-1)}[((n-m-1)!*x^(2*m))/((2.0^(2*m-n))*m!)
//
//		2) Y-n = ((-1)^n)*Yn
//
//========================================================================
//========================================================================
complex<double> bessel_2_complex(int n, complex<double> arg)
{

  complex<double> Yn(0.0, 0.0);

  // get a tolerance for the "infinite" sum
  double tolerance = 100.0*depsilon();

 
  // make sure we calculate the positive order Bessel function
  int k = abs(n);


  // GET BESSEL FUNCTIONS OF THE FIRST KIND
  complex<double> Jn = bessel_1_complex(k, arg);


  // GET TERM SUM 1
  complex<double> sum1(0.0,0.0), sum11(0.0,0.0);


/*
  for(int i = 0; i <= 20; i++)
  {
    sum1 = sum1 + pow((0.0-1.0), (i-1))*(h_s(i) + h_s(i+k))*pow(arg, (2*i))/(pow(2.0, (2*i+k))*dfactorial(i)*dfactorial(i+k));
  }
*/

  // !!! my concern with this do loop is that if a certain term contributes 0 then the 
  // loop may inappropriately exit
  int mm_max = static_cast<int>(2.0*real(arg)) + 1;

  int mm = 0;

  do
  {
    sum11 = sum1;

    sum1 = sum1 + pow((0.0-1.0), (mm-1))*(h_s(mm) + h_s(mm+k))*pow(arg, (2*mm))/(pow(2.0, (2*mm+k))*dfactorial(mm)*dfactorial(mm+k));

    mm = mm + 1;

  } while((fabs(real(sqrt(sum1*conj(sum1) - sum11*conj(sum11)))) > tolerance) || (mm < mm_max));

  sum1 = pow(arg, k)*sum1/(1.0*PI);


  // GET TERM SUM 2
  complex<double> sum2(0.0,0.0);

  for(int m = 0; m <= (k-1); m++)
  {
    sum2 = sum2 + dfactorial((k-m-1))*pow(arg, (2*m))/(pow(2.0, (2*m-k))*dfactorial(m));
  }
  
  sum2 = pow(arg, (0-k))*sum2/(1.0*PI);


  // NOW GET Yn
  Yn = (2.0*Jn/(1.0*PI))*(log(arg/2.0) + EULERC) + sum1 - sum2;


  // NOW WE WILL MAKE USE OF THE BESSEL FUNCTION RELATION FOR NEGATIVE n:
  // Y(n-1) = (-1)^n*Yn
  if(n < 0)
  {
    Yn = pow((0.0-1.0), k)*Yn;
  }


  return Yn;

}