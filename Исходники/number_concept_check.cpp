void test_extra(T)
{
   T t = 1;
   t = abs(t);
   t = abs(t*t);

   t = fabs(t);
   t = fabs(t*t);

   t = sqrt(t);
   t = sqrt(t*t);

   t = floor(t);
   t = floor(t*t);

   t = ceil(t);
   t = ceil(t*t);

   t = trunc(t);
   t = trunc(t*t);

   t = round(t);
   t = round(t*t);

   t = exp(t);
   t = exp(t*t);

   t = log(t);
   t = log(t*t);

   t = log10(t);
   t = log10(t*t);

   t = cos(t);
   t = cos(t*t);

   t = sin(t);
   t = sin(t*t);

   t = tan(t);
   t = tan(t*t);

   t = asin(t);
   t = asin(t*t);

   t = atan(t);
   t = atan(t*t);

   t = acos(t);
   t = acos(t*t);

   t = cosh(t);
   t = cosh(t*t);

   t = sinh(t);
   t = sinh(t*t);

   t = tanh(t);
   t = tanh(t*t);

   double dval = 2;
   t = pow(t, t);
   t = pow(t, t*t);
   t = pow(t, dval);
   t = pow(t*t, t);
   t = pow(t*t, t*t);
   t = pow(t*t, dval);
   t = pow(dval, t);
   t = pow(dval, t*t);

   t = atan2(t, t);
   t = atan2(t, t*t);
   t = atan2(t, dval);
   t = atan2(t*t, t);
   t = atan2(t*t, t*t);
   t = atan2(t*t, dval);
   t = atan2(dval, t);
   t = atan2(dval, t*t);

   t = fmod(t, t);
   t = fmod(t, t*t);
   t = fmod(t, dval);
   t = fmod(t*t, t);
   t = fmod(t*t, t*t);
   t = fmod(t*t, dval);
   t = fmod(dval, t);
   t = fmod(dval, t*t);

   typedef typename T::backend_type backend_type;
   typedef typename backend_type::exponent_type exp_type;
   exp_type e = 0;
   int i = 0;

   t = ldexp(t, i);
   t = ldexp(t*t, i);
   t = ldexp(t, e);
   t = ldexp(t*t, e);

   t = frexp(t, &i);
   t = frexp(t*t, &i);
   t = frexp(t, &e);
   t = frexp(t*t, &e);
}