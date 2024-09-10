/* Compute  log(1 + exp(x))  without overflow (and fast for x > 18)
   For the two cutoffs, consider
   curve(log1p(exp(x)) - x,       33.1, 33.5, n=2^10)
   curve(x+exp(-x) - log1p(exp(x)), 15, 25,   n=2^11)
*/
double Rf_log1pexp(double x) {
    if(x <= 18.) return log1p(exp(x));
    if(x > 33.3) return x;
    // else: 18.0 < x <= 33.3 :
    return x + exp(-x);
}