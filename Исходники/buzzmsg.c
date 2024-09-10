int64_t buzzmsg_deserialize_float(float* data,
                                  buzzdarray_t buf,
                                  uint32_t pos) {
   /* Make sure enough bytes are left to read */
   if(pos + 2*sizeof(uint32_t) > buzzdarray_size(buf)) return -1;
   /* Read the mantissa and the exponent */
   int32_t mant;
   int32_t exp;
   pos = buzzmsg_deserialize_u32((uint32_t*)(&mant), buf, pos);
   pos = buzzmsg_deserialize_u32((uint32_t*)(&exp), buf, pos);
   /* A zero mantissa corresponds to a zero float */
   if(mant == 0) {
      *data = 0;
   }
   else {
      /* We must calculate the float
       *
       * Idea: use the function ldexpf(), which is the opposite of frexpf()
       * For this, we need to transform the mantissa into a normalized
       * fraction in the range [0.5,1)
       *
       * 1. Take the absolute value of the mantissa, which is in [1, MAX_MANTISSA+1]
       * 2. Subtract 1, so it's in [0, MAX_MANTISSA]
       * 3. divide by MAX_MANTISSA, so it's in [0,1)
       * 4. divide by 2, so it's in [0,0.5)
       * 5. Add 0.5, so it's in [0.5,1)
       */
      *data = (float)(abs(mant) - 1) / (2.0f * MAX_MANTISSA) + 0.5f;
      /* Now use ldexpf() to calculate the absolute value */
      *data = ldexpf(*data, exp);
      /* Finally take care of the sign */
      if(mant < 0) *data = -*data;
   }
   return pos;
}