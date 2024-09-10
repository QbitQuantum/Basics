ZZ sum(const Vec<ZZ>& v)
{
   ZZ acc;

   acc = 0;

   for (long i = 0; i < v.length(); i++)
      acc += v[i];

   return acc;
}