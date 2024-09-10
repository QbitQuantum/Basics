Point2F ITR3DMImport::power2Size(const Point2F& ts)
{
   // Find smallest 2^n size that bounds givin size.
   static int table[] =  { 1, 2, 4, 8, 16, 32, 64, 128, 256 };
   int x = 0, y = 0;
   for (; x < sizeof(table) * sizeof(*table); x++)
      if (ts.x <= table[x])
         break;
   for (; y < sizeof(table) * sizeof(*table); y++)
      if (ts.y <= table[y])
         break;
   return Point2F(table[x],table[y]);
};