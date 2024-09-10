static void
calc_primes(char *bitmap, uint64_t max)
{
   uint64_t a,
            r;

   /*** Main algorithm start ***/

   for (a = 3; a <= sqrtl(max); a += 2) {
      if (bitmap[a/2/8] & 1 << ((a/2) % 8))
         continue;

      for (r = a * a; r <= max; r += a * 2)
         bitmap[r/2/8] |= 1 << ((r/2) % 8);
   }

   /*** Main algorithm end ***/

   /* mark 1 as not prime */
   bitmap[0] |= 0x1;
}