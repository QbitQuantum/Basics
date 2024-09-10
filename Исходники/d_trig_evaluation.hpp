 static BOOST_FORCEINLINE A0 base_tancot_eval(const A0& x)
 {
   const A0 zz = sqr(x);
   const A0 num = horn<A0,
     0xc1711fead3299176ll,
     0x413199eca5fc9dddll,
     0xc0c992d8d24f3f38ll
     >(zz);
   const A0 den = horn1<A0,
     0xc189afe03cbe5a31ll,
     0x4177d98fc2ead8efll,
     0xc13427bc582abc96ll,
     0x40cab8a5eeb36572ll
     //    0x3ff0000000000000ll
     >(zz);
   return fma(x, (zz*(num/den)), x);
 }