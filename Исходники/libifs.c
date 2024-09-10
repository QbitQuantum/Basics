void
iterate (control_point *cp,
         int            n,
         int            fuse,
         point         *points)
{
  int    i, j, count_large = 0, count_nan = 0;
  int    xform_distrib[CHOOSE_XFORM_GRAIN];
  double p[3], t, r, dr;
  p[0] = points[0][0];
  p[1] = points[0][1];
  p[2] = points[0][2];

  /*
   * first, set up xform, which is an array that converts a uniform random
   * variable into one with the distribution dictated by the density
   * fields
   */
  dr = 0.0;
  for (i = 0; i < NXFORMS; i++)
    dr += cp->xform[i].density;
  dr = dr / CHOOSE_XFORM_GRAIN;

  j = 0;
  t = cp->xform[0].density;
  r = 0.0;
  for (i = 0; i < CHOOSE_XFORM_GRAIN; i++)
    {
      while (r >= t)
        {
          j++;
          t += cp->xform[j].density;
        }
      xform_distrib[i] = j;
      r += dr;
    }

  for (i = -fuse; i < n; i++)
    {
      /* FIXME: the following is supported only by gcc and c99 */
      int fn = xform_distrib[g_random_int_range (0, CHOOSE_XFORM_GRAIN)];
      double tx, ty, v;

      if (p[0] > 100.0 || p[0] < -100.0 ||
        p[1] > 100.0 || p[1] < -100.0)
      count_large++;
      if (p[0] != p[0])
        count_nan++;

#define coef   cp->xform[fn].c
#define vari   cp->xform[fn].var

      /* first compute the color coord */
      p[2] = (p[2] + cp->xform[fn].color) / 2.0;

      /* then apply the affine part of the function */
      tx = coef[0][0] * p[0] + coef[1][0] * p[1] + coef[2][0];
      ty = coef[0][1] * p[0] + coef[1][1] * p[1] + coef[2][1];

      p[0] = p[1] = 0.0;
      /* then add in proportional amounts of each of the variations */
      v = vari[0];
      if (v > 0.0)
        {
          /* linear */
          double nx, ny;
          nx = tx;
          ny = ty;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[1];
      if (v > 0.0)
        {
          /* sinusoidal */
          double nx, ny;
          nx = sin (tx);
          ny = sin (ty);
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[2];
      if (v > 0.0)
        {
          /* spherical */
          double nx, ny;
          double r2 = tx * tx + ty * ty + 1e-6;
          nx = tx / r2;
          ny = ty / r2;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[3];
      if (v > 0.0)
        {
          /* swirl */
          double r2 = tx * tx + ty * ty;  /* /k here is fun */
          double c1 = sin (r2);
          double c2 = cos (r2);
          double nx = c1 * tx - c2 * ty;
          double ny = c2 * tx + c1 * ty;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[4];
      if (v > 0.0)
        {
          /* horseshoe */
          double a, c1, c2, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            a = atan2(tx, ty);  /* times k here is fun */
          else
            a = 0.0;
          c1 = sin (a);
          c2 = cos (a);
          nx = c1 * tx - c2 * ty;
          ny = c2 * tx + c1 * ty;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[5];
      if (v > 0.0)
        {
          /* polar */
          double nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            nx = atan2 (tx, ty) / G_PI;
          else
            nx = 0.0;

          ny = sqrt (tx * tx + ty * ty) - 1.0;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[6];
      if (v > 0.0)
        {
          /* bent */
          double nx, ny;
          nx = tx;
          ny = ty;
          if (nx < 0.0) nx = nx * 2.0;
          if (ny < 0.0) ny = ny / 2.0;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[7];
      if (v > 0.0)
        {
          /* folded handkerchief */
          double theta, r2, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2( tx, ty );
          else
            theta = 0.0;
          r2 = sqrt (tx * tx + ty * ty);
          nx = sin (theta + r2) * r2;
          ny = cos (theta - r2) * r2;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[8];
      if (v > 0.0)
        {
          /* heart */
          double theta, r2, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2( tx, ty );
          else
            theta = 0.0;
          r2 = sqrt (tx * tx + ty * ty);
          theta *= r2;
          nx = sin (theta) * r2;
          ny = cos (theta) * -r2;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[9];
      if (v > 0.0)
        {
          /* disc */
          double theta, r2, nx, ny;
          if ( tx < -EPS || tx > EPS ||
               ty < - EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          nx = tx * G_PI;
          ny = ty * G_PI;
          r2 = sqrt (nx * nx * ny * ny);
          p[0] += v * sin(r2) * theta / G_PI;
          p[1] += v * cos(r2) * theta / G_PI;
        }

      v = vari[10];
      if (v > 0.0)
        {
          /* spiral */
          double theta, r2;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2( tx, ty );
          else
            theta = 0.0;
          r2 = sqrt (tx * tx + ty * ty) + 1e-6;
          p[0] += v * (cos (theta) + sin (r2)) / r2;
          p[1] += v * (cos (theta) + cos (r2)) / r2;
        }

      v = vari[11];
      if (v > 0.0)
        {
          /* hyperbolic */
          double theta, r2;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          r2 = sqrt (tx * tx + ty * ty) + 1e-6;
          p[0] += v * sin (theta) / r2;
          p[1] += v * cos (theta) * r2;
        }

      v = vari[12];
      if (v > 0.0 )
        {
          double theta, r2;
          /* diamond */
          if ( tx < -EPS || tx > EPS ||
               ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          r2 = sqrt( tx * tx + ty * ty );
          p[0] += v * sin (theta) * cos (r2);
          p[1] += v * cos (theta) * sin (r2);
        }

      v = vari[13];
      if (v > 0.0)
        {
          /* ex */
          double theta, r2, n0, n1, m0, m1;
          if ( tx < -EPS || tx > EPS ||
               ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          r2 = sqrt( tx * tx + ty * ty );
          n0 = sin(theta + r2);
          n1 = cos(theta - r2);
          m0 = n0 * n0 * n0 * r2;
          m1 = n1 * n1 * n1 * r2;
          p[0] += v * (m0 + m1);
          p[1] += v * (m0 - m1);
        }

      v = vari[14];
      if ( v > 0.0)
        {
          double theta, r2, nx, ny;
          /* julia */
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          if (flam3_random_bit ())
            theta += G_PI;
          r2 = pow (tx * tx + ty * ty, 0.25);
          nx = r2 * cos (theta);
          ny = r2 * sin (theta);
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[15];
      if (v > 0.0)
        {
          /* waves */
          double dx, dy, nx, ny;
          dx = coef[2][0];
          dy = coef[2][1];
          nx = tx + coef[1][0] * sin (ty / ((dx * dx) + EPS));
          ny = ty + coef[1][1] * sin (tx / ((dy * dy) + EPS));
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[16];
      if (v > 0.0)
        {
          /* fisheye */
          double theta, r2, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          r2 = sqrt (tx * tx + ty * ty);
          r2 = 2 * r2 / (r2 + 1);
          nx = r2 * cos (theta);
          ny = r2 * sin (theta);
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[17];
      if (v > 0.0)
        {
          /* popcorn */
          double dx, dy, nx, ny;
          dx = tan (3 * ty);
          dy = tan (3 * tx);
          nx = tx + coef[2][0] * sin (dx);
          ny = ty + coef[2][1] * sin (dy);
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[18];
      if (v > 0.0)
        {
          /* exponential */
          double dx, dy, nx, ny;
          dx = exp (tx - 1.0);
          dy = G_PI * ty;
          nx = cos (dy) * dx;
          ny = sin (dy) * dx;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[19];
      if (v > 0.0)
        {
          /* power */
          double theta, r2, tsin, tcos, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          tsin = sin (theta);
          tcos = cos (theta);
          r2 = sqrt (tx * tx + ty * ty);
          r2 = pow (r2, tsin);
          nx = r2 * tcos;;
          ny = r2 * tsin;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[20];
      if (v > 0.0)
        {
          /* cosine */
          double nx, ny;
          nx =  cos (tx * G_PI) * cosh (ty);
          ny = -sin (tx * G_PI) * sinh (ty);
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[21];
      if (v > 0.0)
        {
          /* rings */
          double theta, r2, dx, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0;
          dx = coef[2][0];
          dx = dx * dx + EPS;
          r2 = sqrt (tx * tx + ty * ty);
          r2 = fmod (r2 + dx, 2 * dx) - dx + r2 * (1 - dx);
          nx = cos (theta) * r2;
          ny = sin (theta) * r2;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[22];
      if (v > 0.0)
        {
          /* fan */
          double theta, r2, dx, dy, dx2, nx, ny;
          if (tx < -EPS || tx > EPS ||
              ty < -EPS || ty > EPS)
            theta = atan2 (tx, ty);
          else
            theta = 0.0;
          dx = coef[2][0];
          dy = coef[2][1];
          dx = G_PI * (dx * dx + EPS);
          dx2 = dx / 2;
          r2 = sqrt (tx * tx + ty * ty );
          theta += (fmod (theta + dy, dx) > dx2) ? -dx2: dx2;
          nx = cos (theta) * r2;
          ny = sin (theta) * r2;
          p[0] += v * nx;
          p[1] += v * ny;
        }

      v = vari[23];
      if (v > 0.0)
        {
          /* eyefish */
          double r2;
          r2 = 2.0 * v / (sqrt(tx * tx + ty * ty) + 1.0);
          p[0] += r2 * tx;
          p[1] += r2 * ty;
        }

      v = vari[24];
      if (v > 0.0)
        {
          /* bubble */
          double r2;
          r2 = v / ((tx * tx + ty * ty) / 4 + 1);
          p[0] += r2 * tx;
          p[1] += r2 * ty;
        }

      v = vari[25];
      if (v > 0.0)
        {
          /* cylinder */
          double nx;
          nx = sin (tx);
          p[0] += v * nx;
          p[1] += v * ty;
        }

      v = vari[26];
      if (v > 0.0)
        {
          /* noise */
          double rx, sinr, cosr, nois;
          rx = flam3_random01 () * 2 * G_PI;
          sinr = sin (rx);
          cosr = cos (rx);
          nois = flam3_random01 ();
          p[0] += v * nois * tx * cosr;
          p[1] += v * nois * ty * sinr;
        }

      v = vari[27];
      if (v > 0.0)
        {
          /* blur */
          double rx, sinr, cosr, nois;
          rx = flam3_random01 () * 2 * G_PI;
          sinr = sin (rx);
          cosr = cos (rx);
          nois = flam3_random01 ();
          p[0] += v * nois * cosr;
          p[1] += v * nois * sinr;
        }

      v = vari[28];
      if (v > 0.0)
        {
          /* gaussian */
          double ang, sina, cosa, r2;
          ang = flam3_random01 () * 2 * G_PI;
          sina = sin (ang);
          cosa = cos (ang);
          r2 = v * (flam3_random01 () + flam3_random01 () + flam3_random01 () +
                    flam3_random01 () - 2.0);
          p[0] += r2 * cosa;
          p[1] += r2 * sina;
        }

      /* if fuse over, store it */
      if (i >= 0)
        {
          points[i][0] = p[0];
          points[i][1] = p[1];
          points[i][2] = p[2];
        }
    }
}