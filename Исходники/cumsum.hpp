   typedef typename meta::scalar_of<A0>::type sctype;		
   typedef typename simd::native<sctype, tag::sse_ >  svtype;
   std::cout << " == a0 " << a0 << std::endl;
   svtype a011;
   a011=  _mm256_extractf128_ps(a0, 1);
   svtype a000;
   a000 =  _mm256_extractf128_ps(a0, 0);			
   std::cout << " == a000 " << a000 << std::endl;
   std::cout << " == a011 " << a011 << std::endl;
   svtype a00 =  cumsum(a000);
   svtype a01 =  cumsum(a011); 
   svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
   std::cout << " == a00 " << a00 << std::endl;
   std::cout << " == a01 " << a01 << std::endl;
   std::cout << " == z   " << z   << std::endl; 
   A0 that = {_mm256_insertf128_ps(that,a00, 0)};		
   that =  _mm256_insertf128_ps(that, a01+z, 1); 
   return that;
 }
 NT2_FUNCTOR_CALL_EVAL_IF(1,      double)
 {
   typedef typename meta::scalar_of<A0>::type sctype;		
   typedef typename simd::native<sctype, tag::sse_ >  svtype;
   svtype a000 = { _mm256_extractf128_pd(a0, 0)};			
   svtype a011 = { _mm256_extractf128_pd(a0, 1)};
   svtype a00 =  cumsum(a000);
   svtype a01 =  cumsum(a011); 
   svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
   A0 that = simd::native_cast<A0>(_mm256_insertf128_pd(that,a00, 0));		
   that =  simd::native_cast<A0>(_mm256_insertf128_pd(that, a01+z, 1))			; 
   return that;