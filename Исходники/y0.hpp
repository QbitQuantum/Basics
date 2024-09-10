 template < class AA0 > static inline AA0 branch1(const AA0 & a0)
 {
   typedef typename meta::scalar_of<AA0>::type sAA0; 
   AA0 z = sqr(a0); 
   AA0 p2 = (z-single_constant<AA0, 0x3edd4b3a> ())*
   horner< NT2_HORNER_COEFF_T(sAA0, 5,
                      (0x33cb0920, 
                       0xb71ded71, 
                       0x3a0c1a3e, 
                       0xbc81c8f4, 
                       0x3e2edb4f
                       ) ) > (z);
   return p2+single_constant<AA0, 0x3f22f983>()*log(a0)*j0(a0);
 }