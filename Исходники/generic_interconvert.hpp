R safe_convert_to_float(const LargeInteger& i)
{
   using std::ldexp;
   if(!i)
      return R(0);
   if(std::numeric_limits<R>::is_specialized && std::numeric_limits<R>::max_exponent)
   {
      LargeInteger val(i);
      if(val.sign() < 0)
         val = -val;
      unsigned mb = msb(val);
      if(mb >= std::numeric_limits<R>::max_exponent)
      {
         int scale_factor = (int)mb + 1 - std::numeric_limits<R>::max_exponent;
         BOOST_ASSERT(scale_factor >= 1);
         val >>= scale_factor;
         R result = val.template convert_to<R>();
         if(std::numeric_limits<R>::digits == 0 || std::numeric_limits<R>::digits >= std::numeric_limits<R>::max_exponent)
         {
            //
            // Calculate and add on the remainder, only if there are more
            // digits in the mantissa that the size of the exponent, in 
            // other words if we are dropping digits in the conversion
            // otherwise:
            //
            LargeInteger remainder(i);
            remainder &= (LargeInteger(1) << scale_factor) - 1;
            result += ldexp(safe_convert_to_float<R>(remainder), -scale_factor);
         }
         return i.sign() < 0 ? static_cast<R>(-result) : result;
      }