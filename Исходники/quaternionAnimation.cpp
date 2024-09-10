// Spherical linear interpolation between unit quaternions q1 and q2 with interpolation parameter t.
Quaternion slerp(Quaternion q1, Quaternion q2, float t)
{
   float w1, x1, y1, z1, w2, x2, y2, z2, w3, x3, y3, z3;
   Quaternion q2New;
   float theta, mult1, mult2;

   w1 = q1.getW(); x1 = q1.getX(); y1 = q1.getY(); z1 = q1.getZ(); 
   w2 = q2.getW(); x2 = q2.getX(); y2 = q2.getY(); z2 = q2.getZ();
   
   // Reverse the sign of q2 if q1.q2 < 0.
   if (w1*w2 + x1*x2 + y1*y2 + z1*z2 < 0)  
   {
      w2 = -w2; x2 = -x2; y2 = -y2; z2 = -z2;
   }
	   
   theta = acos(w1*w2 + x1*x2 + y1*y2 + z1*z2);

   if (theta > 0.000001) 
   {
	  mult1 = sin( (1-t)*theta ) / sin( theta );
	  mult2 = sin( t*theta ) / sin( theta );
   }

   // To avoid division by 0 and by very small numbers the approximation of sin(angle)
   // by angle is used when theta is small (0.000001 is chosen arbitrarily).
   else
   {
      mult1 = 1 - t;
	  mult2 = t;
   }

   w3 =  mult1*w1 + mult2*w2;
   x3 =  mult1*x1 + mult2*x2;
   y3 =  mult1*y1 + mult2*y2;
   z3 =  mult1*z1 + mult2*z2;
   
   return *new Quaternion(w3, x3, y3, z3);
}