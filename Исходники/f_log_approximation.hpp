  static inline void
  kernel_log(const A0& a0,A0& fe, A0& x,A0& x2, A0& y, const A0&)
  {
    int_type e;
    bf::tie(x, e) = fast_frexp(a0);
    int_type x_lt_sqrthf = -(Const<float,0x3f3504f3>() > x);
    e += x_lt_sqrthf;
    x += b_and(x, genmask<float>(x_lt_sqrthf))+Const<float,0xbf800000>();
    x2 = sqr(x);
    A0 y1 = fma(Const<float, 0x3d9021bb>() ,x2,Const<float, 0x3def251a>() );
    A0 y2 = fma(Const<float, 0xbdebd1b8>() ,x2,Const<float, 0xbdfe5d4f>() );
    y1 = fma(y1,x2,Const<float, 0x3e11e9bf>() );
    y2 = fma(y2,x2,Const<float, 0xbe2aae50>() );
    y1 = fma(y1,x2,Const<float, 0x3e4cceac>() );
    y2 = fma(y2,x2,Const<float, 0xbe7ffffc>() );
    y1 = fma(y1,x2,Const<float, 0x3eaaaaaa>() );
    y  = fma(x,y2,y1)*x*x2;
    fe = tofloat(e);
 }