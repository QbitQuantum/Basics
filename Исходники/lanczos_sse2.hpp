inline double lanczos13m53::lanczos_sum<double>(const double& x)
{
   static const ALIGN16 double coeff[26] = {
      static_cast<double>(2.506628274631000270164908177133837338626L),
      static_cast<double>(1u),
      static_cast<double>(210.8242777515793458725097339207133627117L),
      static_cast<double>(66u),
      static_cast<double>(8071.672002365816210638002902272250613822L),
      static_cast<double>(1925u),
      static_cast<double>(186056.2653952234950402949897160456992822L),
      static_cast<double>(32670u),
      static_cast<double>(2876370.628935372441225409051620849613599L),
      static_cast<double>(357423u),
      static_cast<double>(31426415.58540019438061423162831820536287L),
      static_cast<double>(2637558u),
      static_cast<double>(248874557.8620541565114603864132294232163L),
      static_cast<double>(13339535u),
      static_cast<double>(1439720407.311721673663223072794912393972L),
      static_cast<double>(45995730u),
      static_cast<double>(6039542586.35202800506429164430729792107L),
      static_cast<double>(105258076u),
      static_cast<double>(17921034426.03720969991975575445893111267L),
      static_cast<double>(150917976u),
      static_cast<double>(35711959237.35566804944018545154716670596L),
      static_cast<double>(120543840u),
      static_cast<double>(42919803642.64909876895789904700198885093L),
      static_cast<double>(39916800u),
      static_cast<double>(23531376880.41075968857200767445163675473L),
      static_cast<double>(0u)
   };
   register __m128d vx = _mm_load1_pd(&x);
   register __m128d sum_even = _mm_load_pd(coeff);
   register __m128d sum_odd = _mm_load_pd(coeff+2);
   register __m128d nc_odd, nc_even;
   register __m128d vx2 = _mm_mul_pd(vx, vx);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 4);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 6);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 8);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 10);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 12);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 14);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 16);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 18);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 20);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 22);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 24);
   sum_odd = _mm_mul_pd(sum_odd, vx);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_even = _mm_add_pd(sum_even, sum_odd);


   double ALIGN16 t[2];
   _mm_store_pd(t, sum_even);
   
   return t[0] / t[1];
}