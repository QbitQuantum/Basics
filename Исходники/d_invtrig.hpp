 static inline A0_n asin(const A0_n a0_n)
 {
   const A0 a0 = { a0_n };
   typedef typename meta::scalar_of<A0>::type sA0;
   A0 x = nt2::abs(a0);
   const A0 pio4 =  Pio_4<A0>();
   const bA0 small=  lt(x, Sqrteps<A0>());
   const A0 morebits = double_constant<A0, 0xbc91a62633145c07ll>();
   const A0 ct1      = double_constant<A0, 0x3fe4000000000000ll>();
   A0 zz1 = oneminus(x);
   const A0 vp = zz1*horner< NT2_HORNER_COEFF_T(sA0, 5,
                                                (0x3f684fc3988e9f08ll,
                                                 0xbfe2079259f9290fll,
                                                 0x401bdff5baf33e6all,
                                                 0xc03991aaac01ab68ll,
                                                 0x403c896240f3081dll)
                                                )>(zz1)/
                   horner< NT2_HORNER_COEFF_T(sA0, 5,
                                              (0x3ff0000000000000ll,
                                               0xc035f2a2b6bf5d8cll,
                                               0x40626219af6a7f42ll,
                                               0xc077fe08959063eell,
                                               0x40756709b0b644bell)
                                              )>(zz1);
   zz1 =  sqrt(zz1+zz1);
   A0 z = pio4-zz1;
   zz1 = fma(zz1, vp, morebits);
   z =  z-zz1;
   zz1 = z+pio4;
   A0 zz2 = sqr(a0);
   z = zz2*horner< NT2_HORNER_COEFF_T(sA0, 6,
                                  (0x3f716b9b0bd48ad3ll,
                                   0xbfe34341333e5c16ll,
                                   0x4015c74b178a2dd9ll,
                                   0xc0304331de27907bll,
                                   0x40339007da779259ll,
                                   0xc020656c06ceafd5ll)
                                  )>(zz2)/
         horner< NT2_HORNER_COEFF_T(sA0, 6,
                                  (0x3ff0000000000000ll,
                                   0xc02d7b590b5e0eabll,
                                   0x40519fc025fe9054ll,
                                   0xc06265bb6d3576d7ll,
                                   0x4061705684ffbf9dll,
                                   0xc04898220a3607acll)
                                  )>(zz2);
   zz2 = x*z+x;
   return if_nan_else( gt(x, One<A0>())
                     , b_xor ( select( small
                                     , x
                                     , select( gt(x, ct1)
                                             , zz1
                                             , zz2
                                             )
                                     )
                             , bitofsign(a0)
                             )
                     );
 }