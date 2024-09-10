 void power(ElementType& result, const ElementType& a, int n) const
 {
   if (is_zero(a))
     set_zero(result);
   else if (n < 0)
     {
       invert(result, a);
       fq_zech_pow_ui(&result, &result, -n, mContext);
     }
   else
     fq_zech_pow_ui(&result, &a, n, mContext);
 }