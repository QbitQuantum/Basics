double ntail(double zval) 
/** normal distribution tail area 
 uses erfc 
*/

{
  double pi,  t ;
  double p, q, d ;

  if (zval == 0.0) return 0.5 ;
  if (zval<0.0) return (1.0 - ntail(-zval)) ;
  if (zval<ZLIM) {
   t = zval/sqrt(2.0) ;
   q = erfc(t)/2.0 ;
   return q ;
  }

  pi = 2.0*acos(0.0)  ;

  t = exp(-0.5*zval*zval) ;
  t /= (sqrt(2.0*pi) * zval) ;

  return t ;

}