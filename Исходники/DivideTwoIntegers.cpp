 int divide(int dividend, int divisor) {
     bool isPos = false;
     if(0 == dividend) {return 0;}
     if((dividend > 0 && divisor > 0) || (dividend < 0 && divisor < 0))
     {
         isPos = true;
     }
     else
     {
         isPos = false;
     }
     long long divdendll = dividend;
     long long divisorll = divisor;
     if(divdendll < 0) {divdendll = 0 - divdendll;}
     if(divisorll < 0) {divisorll = 0 - divisorll;}
     if(divdendll < divisor) {return 0;}
     int n = GetBound(divdendll, divisorll);
     long long ret = BSearch(divdendll, divisorll, n);
     if(!isPos) {ret = 0 - ret;}
     return ret;
 }