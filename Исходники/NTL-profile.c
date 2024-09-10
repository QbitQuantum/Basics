void run_triangle(unsigned long max_bits, double ratio)
{
   int max_iter = (int) ceil(log((double) max_bits) / log(ratio));

   unsigned long last_length = 0;
   unsigned long i;
   for (i = 0; i <= max_iter; i++)
   {
      unsigned long length = (unsigned long) floor(powl(ratio, i));
      if (length != last_length)
      {
         last_length = length;

         unsigned long last_bits = 0;
         unsigned long j;
         for (j = 0; j <= max_iter; j++)
         {
            unsigned long bits = (unsigned long) floor(powl(ratio, j));
            if (bits != last_bits)
            {
               last_bits = bits;

               if (bits * length < max_bits)
                  prof2d_sample(length, bits, NULL);
            }
         }
      }
   }
}