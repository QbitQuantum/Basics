/*************************************************************************
Inverse binomial distribution

Finds the event probability p such that the sum of the
terms 0 through k of the Binomial probability density
is equal to the given cumulative probability y.

This is accomplished using the inverse beta integral
function and the relation

1 - p = incbi( n-k, k+1, y ).

ACCURACY:

Tested at random points (a,b,p).

              a,b                     Relative error:
arithmetic  domain     # trials      peak         rms
 For p between 0.001 and 1:
   IEEE     0,100       100000      2.3e-14     6.4e-16
   IEEE     0,10000     100000      6.6e-12     1.2e-13
 For p between 10^-6 and 0.001:
   IEEE     0,100       100000      2.0e-12     1.3e-14
   IEEE     0,10000     100000      1.5e-12     3.2e-14

Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*************************************************************************/
double invbinomialdistribution(int k, int n, double y)
{
    double result;
    double dk;
    double dn;
    double p;

    ap::ap_error::make_assertion(k>=0&&k<n, "Domain error in InvBinomialDistribution");
    dn = n-k;
    if( k==0 )
    {
        if( ap::fp_greater(y,0.8) )
        {
            p = -expm1(log1p(y-1.0)/dn);
        }
        else
        {
            p = 1.0-pow(y, 1.0/dn);
        }
    }
    else
    {
        dk = k+1;
        p = incompletebeta(dn, dk, 0.5);
        if( ap::fp_greater(p,0.5) )
        {
            p = invincompletebeta(dk, dn, 1.0-y);
        }
        else
        {
            p = 1.0-invincompletebeta(dn, dk, y);
        }
    }
    result = p;
    return result;
}