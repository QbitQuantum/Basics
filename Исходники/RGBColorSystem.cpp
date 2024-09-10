void RGBColorSystem::Data::Initialize()
{
   /*
    * Normalize luminance coefficients
    */
   double s = Y.Sum();
   if ( 1 + s == 1 )
      throw Error( "Invalid luminance coefficients in RGB working color space initialization." );
   Y /= s;

   /*
    * RGB -> XYZ transformation matrix M
    */
   M = SetupMatrix( x, y, Y );

   /*
    * CIE X and CIE Z normalization coefficients
    */
   mX = M11 + M12 + M13;
   mZ = M31 + M32 + M33;

   /*
    * XYZ -> RGB inverse matrix M_
    */
   M_ = InverseMatrix( M );

   /*
    * Inverse gamma
    */
   if ( 1 + gamma == 1 || gamma < 0 )
      throw Error( "Invalid gamma value in RGB working color space initialization." );
   gammaInv = 1/gamma;

   /*
    * Find normalization coefficients for CIE a, b, c channels
    *
    * The idea here is to maximize dynamic range usage for each channel
    * (coding efficiency) while ensuring that they will be constrained to the
    * nominal range [0,1].
    */

   sample minab = 100, maxab = -100, maxc = -100;

   int minabR = 0, minabG = 0, minabB = 0;
   int maxabR = 0, maxabG = 0, maxabB = 0;
   int maxcR = 0, maxcG = 0, maxcB = 0;

   for ( int ri = 0; ri < 10; ++ri )
   {
      sample R = sample( ri/9.0 );

      for ( int gi = 0; gi < 10; ++gi )
      {
         sample G = sample( gi/9.0 );

         for ( int bi = 0; bi < 10; ++bi )
         {
            sample B = sample( bi/9.0 );

            sample X, Y, Z;
            RGBToCIEXYZ( X, Y, Z, R, G, B );

            RGBColorSystem::XYZLab( X );
            RGBColorSystem::XYZLab( Y );
            RGBColorSystem::XYZLab( Z );

            sample a = 5*(X - Y);
            sample b = 2*(Y - Z);
            sample c = Sqrt( a*a + b*b );

            sample mn = Min( a, b );
            sample mx = Max( a, b );

            if ( mn < minab )
            {
               minab = mn;
               minabR = ri;
               minabG = gi;
               minabB = bi;
            }

            if ( mx > maxab )
            {
               maxab = mx;
               maxabR = ri;
               maxabG = gi;
               maxabB = bi;
            }

            if ( c > maxc )
            {
               maxc = c;
               maxcR = ri;
               maxcG = gi;
               maxcB = bi;
            }
         }
      }
   }

   sample R0, R1, G0, G1, B0, B1;

   R0 = Max( 0, minabR-1 )/9.0;
   R1 = Min( 9, minabR+1 )/9.0;

   G0 = Max( 0, minabG-1 )/9.0;
   G1 = Min( 9, minabG+1 )/9.0;

   B0 = Max( 0, minabB-1 )/9.0;
   B1 = Min( 9, minabB+1 )/9.0;

   for ( sample R = R0; R < R1; R += 0.01 )
      for ( sample G = G0; G < G1; G += 0.01 )
         for ( sample B = B0; B < B1; B += 0.01 )
         {
            sample X, Y, Z;
            RGBToCIEXYZ( X, Y, Z, R, G, B );

            RGBColorSystem::XYZLab( X );
            RGBColorSystem::XYZLab( Y );
            RGBColorSystem::XYZLab( Z );

            sample mn = Min( 5*(X - Y), 2*(Y - Z) );
            if ( mn < minab )
               minab = mn;
         }

   R0 = Max( 0, maxabR-1 )/9.0;
   R1 = Min( 9, maxabR+1 )/9.0;

   G0 = Max( 0, maxabG-1 )/9.0;
   G1 = Min( 9, maxabG+1 )/9.0;

   B0 = Max( 0, maxabB-1 )/9.0;
   B1 = Min( 9, maxabB+1 )/9.0;

   for ( sample R = R0; R < R1; R += 0.01 )
      for ( sample G = G0; G < G1; G += 0.01 )
         for ( sample B = B0; B < B1; B += 0.01 )
         {
            sample X, Y, Z;
            RGBToCIEXYZ( X, Y, Z, R, G, B );

            RGBColorSystem::XYZLab( X );
            RGBColorSystem::XYZLab( Y );
            RGBColorSystem::XYZLab( Z );

            sample mx = Max( 5*(X - Y), 2*(Y - Z) );
            if ( mx > maxab )
               maxab = mx;
         }

   R0 = Max( 0, maxcR-1 )/9.0;
   R1 = Min( 9, maxcR+1 )/9.0;

   G0 = Max( 0, maxcG-1 )/9.0;
   G1 = Min( 9, maxcG+1 )/9.0;

   B0 = Max( 0, maxcB-1 )/9.0;
   B1 = Min( 9, maxcB+1 )/9.0;

   for ( sample R = R0; R < R1; R += 0.01 )
      for ( sample G = G0; G < G1; G += 0.01 )
         for ( sample B = B0; B < B1; B += 0.01 )
         {
            sample X, Y, Z;
            RGBToCIEXYZ( X, Y, Z, R, G, B );

            RGBColorSystem::XYZLab( X );
            RGBColorSystem::XYZLab( Y );
            RGBColorSystem::XYZLab( Z );

            sample a = 5*(X - Y);
            sample b = 2*(Y - Z);
            sample c = Sqrt( a*a + b*b );

            if ( c > maxc )
               maxc = c;
         }

   abOffset = -minab + 0.05;
   abDelta  =  maxab - minab + 0.1;
   cDelta   =  maxc + 0.05;
}