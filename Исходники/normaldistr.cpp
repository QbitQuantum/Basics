/*************************************************************************
Normal distribution function

Returns the area under the Gaussian probability density
function, integrated from minus infinity to x:

                           x
                            -
                  1        | |          2
   ndtr(x)  = ---------    |    exp( - t /2 ) dt
              sqrt(2pi)  | |
                          -
                         -inf.

            =  ( 1 + erf(z) ) / 2
            =  erfc(z) / 2

where z = x/sqrt(2). Computation is via the functions
erf and erfc.


ACCURACY:

                     Relative error:
arithmetic   domain     # trials      peak         rms
   IEEE     -13,0        30000       3.4e-14     6.7e-15

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1988, 1992, 2000 by Stephen L. Moshier
*************************************************************************/
double normaldistribution(double x)
{
    double result;

    result = 0.5*(erf(x/1.41421356237309504880)+1);
    return result;
}