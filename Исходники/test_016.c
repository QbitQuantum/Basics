static void
calc_primes(char *bitmap, uint64_t max)
{
   char     *bmp,
            *bitmap_end = bitmap + 32*1024;
   uint64_t  a,
             cur;
   int       i,
             a_i,
             offsets[8];

   /*** Main algorithm start ***/
   for (cur = 0; cur <= max; cur += 32*1024*30, bitmap_end += 32*1024) {

      for (a = 7, a_i = 1; a <= sqrtl(cur + 32*1024*30); a += diff[a_i++%8]) {
         if (bitmap[a / 30] & 1 << (a_i%8))
            continue;

         for (i = 0; i < 8; i++)
            offsets[num2bit(a * bval[i])] = a * bval[i] / 30;

         for (bmp = bitmap + MAX(a * (a / 30), (cur / 30) / a * a);
              bmp < bitmap_end;
              bmp += a) {
            for (i = 0; i < 8; i++)
               *(bmp + offsets[i]) |= 1 << i;
         }
      }

      /* First byte gets clobbered for the first block */
      if (cur == 0)
         bitmap[0] = 0x1;
   }

   /*** Main algorithm end ***/
}