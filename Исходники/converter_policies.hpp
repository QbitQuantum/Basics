  static source_type nearbyint ( argument_type s )
  {
    // Algorithm contributed by Guillaume Melquiond
    
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif    

    // only works inside the range not at the boundaries
    S a = floor(s); 
    S b = ceil(s);  
    
    S c = (s - a) - (b - s); // the "good" subtraction
    
    if ( c < static_cast<S>(0.0) ) 
      return a;
    else if ( c >  static_cast<S>(0.0) )
      return b;
    else 
      return 2 * floor(b / static_cast<S>(2.0)); // needs to behave sanely
  }