sl_def(do_test, void)
{
#define x values[p].d
#define xf values[p].f
#define y values[p+1].d
#define yf values[p+1].f
#define n values[p+2].i
#define nl values[p+2].l

#define call1(F)                                 \
  values[p].desc = #F;                           \
  values[p].d = F(x);                            \
  ++p;                                           \
  values[p].desc = #F "f";                       \
  values[p].f = F ## f (xf);                     \
  ++p


#define call1i(F)				\
  values[p].desc = #F;				\
  values[p].i = F(x);                           \
  ++p

#define call2(F)                                  \
  values[p].desc = #F;                            \
  values[p].d = F(x, y);                          \
  p += 2;                                         \
  values[p].desc = #F "f";                        \
  values[p].f = F ## f (xf, yf);                  \
  p += 2

#define call2i(F)                                 \
  values[p].desc = #F;                            \
  values[p].i = F(x, y);                          \
  p += 2;                                         \
  values[p].desc = #F "f";                        \
  values[p].i = F(xf, yf);                        \
  p += 2

  /* classify */
  call1i(fpclassify);
  call1i(signbit);
  call1i(isfinite);
  call1i(isnormal);
  call1i(isnan);
  call1i(isinf);

  /* trig */
  call1(acos);
  call1(asin);
  call1(atan);
  call2(atan2);
  call1(cos);
  call1(sin);
  call1(tan);

  /* hyperbolic */
  call1(acosh);
  call1(asinh);
  call1(atanh);
  call1(cosh);
  call1(sinh);
  call1(tanh);

  /* exp/log */
  call1(exp);
  call1(exp2);
  call1(expm1);

  values[p].desc = "frexp";
  values[p].d = frexp(x, &values[p+1].i);
  p += 2;

  values[p].desc = "frexpf";
  values[p].f = frexpf(xf, &values[p+1].i);
  p += 2;

  values[p].desc = "ilogb";
  values[p].i = ilogb(x); p++;
  values[p].desc = "ilogbf";
  values[p].i = ilogbf(xf); p++;

  values[p].desc = "ldexp";
  values[p].d = ldexp(x, n); p+=3;
  values[p].desc = "ldexpf";
  values[p].f = ldexpf(xf, n); p+=3;

  call1(log);
  call1(log10);
  call1(log1p);
  call1(log2);
  call1(logb);

  values[p].desc = "modf";
  values[p].d = modf(x, &y); 
  p += 2;

  values[p].desc = "modff";
  values[p].f = modff(xf, &yf);
  p += 2;

  values[p].desc = "scalbn";
  values[p].d = scalbn(x, n); p+=3;
  values[p].desc = "scalbnf";
  values[p].f = scalbnf(xf, n); p+=3;

  values[p].desc = "scalbln";
  values[p].d = scalbln(x, nl); p+=3;
  values[p].desc = "scalblnf";
  values[p].f = scalblnf(xf, nl); p+=3;

  /* power/abs */

  call1(cbrt);
  call1(fabs);
  call2(hypot);
  call2(pow);
  call1(sqrt);

  /* error/gamma */
  call1(erf);
  call1(erfc);
  call1(lgamma);
  call1(tgamma); 
  call1(ceil);
  call1(floor);
  call1(nearbyint);
  call1(rint);
  call1(lrint);

  values[p].desc = "lrint";
  values[p].l = lrint(x); p++;
  values[p].desc = "lrintf";
  values[p].l = lrintf(xf); p++;
  values[p].desc = "llrint";
  values[p].ll = llrint(x); p++;
  values[p].desc = "llrintf";
  values[p].ll = llrintf(xf); p++;

  call1(round);

  values[p].desc = "lround";
  values[p].l = lround(x); p++;
  values[p].desc = "lroundf";
  values[p].l = lroundf(xf); p++;
  values[p].desc = "llround";
  values[p].ll = llround(x); p++;
  values[p].desc = "llroundf";
  values[p].ll = llroundf(xf); p++;

  call1(trunc);

  /* rem/mod */
  call2(fmod);
  call2(remainder);

  values[p].desc = "remquo";
  values[p].d = remquo(x, y, &values[p+1].i); p+=2;
  values[p].desc = "remquof";
  values[p].f = remquof(xf, yf, &values[p+1].i); p+=2;

  call2(copysign);

  /* nan */

  values[p].desc = "nan";
  values[p].d = nan(""); ++p;
  values[p].desc = "nanf";
  values[p].f = nanf(""); ++p;

  call2(nextafter);

  /* min/max/dim */
  call2(fdim);
  call2(fmax);
  call2(fmin);
  values[p].desc = "fma";
  values[p].d = fma(x, y, values[p+2].d); p+=3;
  values[p].desc = "fmaf";
  values[p].d = fmaf(xf, yf, values[p+2].f); p+=3;

  /* comp */
  call2i(isgreater);
  call2i(isgreaterequal);
  call2i(isless);
  call2i(islessequal);
  call2i(islessgreater);
  call2i(isunordered);

#undef x
#undef xf
#undef y
#undef n
}