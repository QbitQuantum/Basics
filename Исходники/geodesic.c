static void geod_inv() {
      double      th1,th2,thm,dthm,dlamm,dlam,sindlamm,costhm,sinthm,cosdthm,
      sindthm,L,E,cosd,d,X,Y,T,sind,tandlammp,u,v,D,A,B;


            /*   Stuff the WGS84 projection parameters as necessary
      To avoid having to include <geodesic,h>
            */

      ellipse = 1;
      f = 1.0 / WGSinvf;       /* WGS84 ellipsoid flattening parameter */
      geod_a = WGS84_semimajor_axis_meters;

      es = 2 * f - f * f;
      onef = sqrt(1. - es);
      geod_f = 1 - onef;
      f2 = geod_f/2;
      f4 = geod_f/4;
      f64 = geod_f*geod_f/64;


      if (ellipse) {
            th1 = atan(onef * tan(phi1));
            th2 = atan(onef * tan(phi2));
      } else {
            th1 = phi1;
            th2 = phi2;
      }
      thm = .5 * (th1 + th2);
      dthm = .5 * (th2 - th1);
      dlamm = .5 * ( dlam = adjlon(lam2 - lam1) );
      if (fabs(dlam) < DTOL && fabs(dthm) < DTOL) {
            al12 =  al21 = geod_S = 0.;
            return;
      }
      sindlamm = sin(dlamm);
      costhm = cos(thm);      sinthm = sin(thm);
      cosdthm = cos(dthm);    sindthm = sin(dthm);
      L = sindthm * sindthm + (cosdthm * cosdthm - sinthm * sinthm)
                  * sindlamm * sindlamm;
      d = acos(cosd = 1 - L - L);
      if (ellipse) {
            E = cosd + cosd;
            sind = sin( d );
            Y = sinthm * cosdthm;
            Y *= (Y + Y) / (1. - L);
            T = sindthm * costhm;
            T *= (T + T) / L;
            X = Y + T;
            Y -= T;
            T = d / sind;
            D = 4. * T * T;
            A = D * E;
            B = D + D;
            geod_S = geod_a * sind * (T - f4 * (T * X - Y) +
                        f64 * (X * (A + (T - .5 * (A - E)) * X) -
                        Y * (B + E * Y) + D * X * Y));
            tandlammp = tan(.5 * (dlam - .25 * (Y + Y - E * (4. - X)) *
                        (f2 * T + f64 * (32. * T - (20. * T - A)
                        * X - (B + 4.) * Y)) * tan(dlam)));
      } else {
            geod_S = geod_a * d;
            tandlammp = tan(dlamm);
      }
      u = atan2(sindthm , (tandlammp * costhm));
      v = atan2(cosdthm , (tandlammp * sinthm));
      al12 = adjlon(TWOPI + v - u);
      al21 = adjlon(TWOPI - v - u);
}