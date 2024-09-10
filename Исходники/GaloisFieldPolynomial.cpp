   GaloisFieldPolynomial& GaloisFieldPolynomial::operator%=(const GaloisFieldPolynomial& gfp)
   {

      if ((gf == gfp.gf) &&
          (deg() >= gfp.deg()) &&
          (gfp.deg() >= 0)
         )
      {

         GaloisFieldPolynomial quotent(gf, deg() - gfp.deg() + 1);
         GaloisFieldPolynomial remainder(gf, gfp.deg() - 1);

         for(int i = deg(); i >= 0; i--)
         {
            if (i <= (int)quotent.deg())
              quotent[i] = remainder[remainder.deg()] / gfp[gfp.deg()];

            for(int j = remainder.deg(); j > 0; j--)
            {
               remainder[j] = remainder[j - 1] + (quotent[i] * gfp[j]);
            }
            remainder[0] = poly[i] + (quotent[i] * gfp[0]);
         }

         simplify(remainder);
         poly = remainder.poly;
      }

      return *this;

   }