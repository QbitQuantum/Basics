static void
calc_primes(char *bitmap, uint64_t max)
{
   uint64_t a,
            r;

   /*** Main algorithm start ***/

   for (a = 2; a <= sqrtl(max); a++) {
      if (bitmap[a / 8] & 1 << (a % 8))
         continue;

      for (r = a * a; r <= max; r += a)
         bitmap[r / 8] |= 1 << (r % 8);
   }

   /*** Main algorithm end ***/

   /* mark bit 0 and 1 as not prime */
   bitmap[0] |= 0x3;
}