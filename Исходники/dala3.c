double sqwavering (double x0, double y0, double radius, double len, int nwaves)
{
   double delta;
   double theta;
   double degrees;
   double xvec, yvec;
   double x1, y1;
   double x2, y2;
   int i;
   
   /* Number of half-waves; must be even */
   nwaves *= 2;
   
   delta = (2.0 * M_PI) / (double)nwaves;
   degrees = 360.0 / (double)nwaves;

   for (i = 0; i < nwaves; i++) {
      theta = (double)i * delta;
      xvec = cos (theta);
      yvec = sin (theta);
      
      x1 = xvec * radius;
      y1 = yvec * radius;
      
      x2 = xvec * (radius + len);
      y2 = yvec * (radius + len);
      
      if (i == 0)
         moveto (x0 + x2, y0 + y2);

      if (i & 1)
         lineto (x0 + x2, y0 + y2);
      else
         lineto (x0 + x1, y0 + y1);

      arc (x0, y0, degrees);
   }
   
   return (radius + len);
}