void bisection_method(T& low, T& hi, RootedFunction f, const T& tol = std::numeric_limits<T>::epsilon()) 
{
  using std::fabs;
  
  T low_value = f(low);
  T hi_value = f(hi);
  
  if( low_value * hi_value > 0.0 )
    return;
  
  while(fabs(hi - low) > tol) {
    
    T mid = 0.5 * (hi + low);
    T mid_value = f(mid);
    
    if(mid_value * hi_value > 0.0) {
      hi = mid;
      hi_value = mid_value;
    } else {
      low = mid;
      low_value = mid_value;
    };
    
  };
  
};