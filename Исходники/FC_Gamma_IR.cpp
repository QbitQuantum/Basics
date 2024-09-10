 double dbeta(double x, double a, double b)
 {
     double out = (a-1)*std::log(x) + 
         (b-1)*std::log(1-x) + 
         (lgamma(a+b)) - 
         ((lgamma(a)) + (lgamma(b)));
     return(out);
 }