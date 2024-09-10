static void
make_gasket (logo_configuration *dc, int wire)
{
  int i;
  int points_size;
  int npoints = 0;
  int nctrls = 0;
  int res = 360/8;
  GLfloat d2r = M_PI / 180;

  GLfloat thick2 = (dc->gasket_thickness / dc->gasket_size) / 2;

  GLfloat *pointsx0, *pointsy0, *pointsx1, *pointsy1, *normals;

  GLfloat r0  = 0.780;  /* 395 */
  GLfloat r1a = 0.855;                /* top of wall below upper left hole */
  GLfloat r1b = 0.890;                /* center of upper left hole */
  GLfloat r1c = 0.922;                /* bottom of wall above hole */
  GLfloat r1  = 0.928;  /* 471 */
  GLfloat r2  = 0.966;  /* 490 */
  GLfloat r3  = 0.984;  /* 499 */
  GLfloat r4  = 1.000;  /* 507 */
  GLfloat r5  = 1.090;  /* 553 */

  GLfloat ctrl_r[100], ctrl_th[100];

  glPushMatrix();

# define POINT(r,th) \
    ctrl_r [nctrls] = r, \
    ctrl_th[nctrls] = (th * d2r), \
    nctrls++

  POINT (0.829, 0);      /* top indentation, right half */
  POINT (0.831, 0.85);
  POINT (0.835, 1.81);
  POINT (0.841, 2.65);
  POINT (0.851, 3.30);
  POINT (0.862, 3.81);
  POINT (0.872, 3.95);

  POINT (r4,    4.0);   /* moving clockwise... */
  POINT (r4,   48.2);
  POINT (r1,   48.2);
  POINT (r1,   54.2);
  POINT (r2,   55.8);
  POINT (r2,   73.2);
  POINT (r1,   74.8);
  POINT (r1,  101.2);
  POINT (r3,  103.4);
  POINT (r3,  132.0);
  POINT (r1,  133.4);

  POINT (r1,  180.7);
  POINT (r2,  183.6);
  POINT (r2,  209.8);
  POINT (r1,  211.0);
  POINT (r1,  221.8);
  POINT (r5,  221.8);
  POINT (r5,  223.2);
  POINT (r4,  223.2);

  POINT (r4,  316.8);      /* upper left indentation */
  POINT (0.990, 326.87);
  POINT (0.880, 327.21);
  POINT (0.872, 327.45);
  POINT (0.869, 327.80);
  POINT (0.867, 328.10);

  POINT (0.867, 328.85);
  POINT (0.869, 329.15);
  POINT (0.872, 329.50);
  POINT (0.880, 329.74);
  POINT (0.990, 330.08);

  POINT (r4,  339.0);
  if (! wire)
    {
      POINT (r1a, 339.0);      /* cut-out disc */
      POINT (r1a, 343.0);
    }
  POINT (r4,  343.0);
  POINT (r4,  356.0);

  POINT (0.872, 356.05);   /* top indentation, left half */
  POINT (0.862, 356.19);
  POINT (0.851, 356.70);
  POINT (0.841, 357.35);
  POINT (0.835, 358.19);
  POINT (0.831, 359.15);
  POINT (0.829, 360);
# undef POINT

  points_size = res + (nctrls * 2);
  pointsx0 = (GLfloat *) malloc (points_size * sizeof(GLfloat));
  pointsy0 = (GLfloat *) malloc (points_size * sizeof(GLfloat));
  pointsx1 = (GLfloat *) malloc (points_size * sizeof(GLfloat));
  pointsy1 = (GLfloat *) malloc (points_size * sizeof(GLfloat));
  normals  = (GLfloat *) malloc (points_size * sizeof(GLfloat) * 2);

  npoints = 0;
  for (i = 1; i < nctrls; i++)
    {
      GLfloat from_r  = ctrl_r [i-1];
      GLfloat from_th = ctrl_th[i-1];
      GLfloat to_r    = ctrl_r [i];
      GLfloat to_th   = ctrl_th[i];

      GLfloat step = 2*M_PI / res;
      int nsteps = 1 + ((to_th - from_th) / step);
      int j;

      for (j = 0; j < nsteps + (i == nctrls-1); j++)
        {
          GLfloat r  = from_r  + (j * (to_r  - from_r)  / nsteps);
          GLfloat th = from_th + (j * (to_th - from_th) / nsteps);

          GLfloat cth = cos(th) * dc->gasket_size;
          GLfloat sth = sin(th) * dc->gasket_size;

          pointsx0[npoints] = r0 * cth;  /* inner ring */
          pointsy0[npoints] = r0 * sth;
          pointsx1[npoints] = r  * cth;  /* outer ring */
          pointsy1[npoints] = r  * sth;
          npoints++;

          if (npoints >= points_size) abort();
        }
    }

  /* normals for the outer ring */
  for (i = 1; i < npoints; i++)
    {
      XYZ a, b, c, n;
      a.x = pointsx1[i-1];
      a.y = pointsy1[i-1];
      a.z = 0;
      b.x = pointsx1[i];
      b.y = pointsy1[i];
      b.z = 0;
      c = b;
      c.z = 1;
      n = calc_normal (a, b, c);
      normals[(i-1)*2  ] = n.x;
      normals[(i-1)*2+1] = n.y;
    }

  glRotatef(-90, 0, 1, 0);
  glRotatef(180, 0, 0, 1);

  if (wire)
    {
      GLfloat z;
      for (z = -thick2; z <= thick2; z += thick2*2)
        {
# if 1
          /* inside edge */
          glBegin (GL_LINE_LOOP);
          for (i = 0; i < npoints; i++)
            glVertex3f (pointsx0[i], pointsy0[i], z);
          glEnd();

          /* outside edge */
          glBegin (GL_LINE_LOOP);
          for (i = 0; i < npoints; i++)
            glVertex3f (pointsx1[i], pointsy1[i], z);
          glEnd();
# else
          for (i = 1; i < npoints; i++)
            {
              glBegin (GL_LINE_STRIP);
              glVertex3f (pointsx0[i-1], pointsy0[i-1], z);
              glVertex3f (pointsx0[i  ], pointsy0[i  ], z);
              glVertex3f (pointsx1[i  ], pointsy1[i  ], z);
              glVertex3f (pointsx1[i-1], pointsy1[i-1], z);
              glEnd();
            }
# endif
        }
#if 1
      glBegin (GL_LINES);
      for (i = 0; i < npoints; i++)
        {
          /* inside rim */
          glVertex3f (pointsx0[i], pointsy0[i], -thick2);
          glVertex3f (pointsx0[i], pointsy0[i],  thick2);
          /* outside rim */
          glVertex3f (pointsx1[i], pointsy1[i], -thick2);
          glVertex3f (pointsx1[i], pointsy1[i],  thick2);
        }
      glEnd();
#endif
    }
  else
    {
      /* top */
      glFrontFace(GL_CW);
      glNormal3f(0, 0, -1);
      glBegin (GL_QUAD_STRIP);
      for (i = 0; i < npoints; i++)
        {
          glVertex3f (pointsx0[i], pointsy0[i], -thick2);
          glVertex3f (pointsx1[i], pointsy1[i], -thick2);
        }
      glEnd();

      /* bottom */
      glFrontFace(GL_CCW);
      glNormal3f(0, 0, 1);
      glBegin (GL_QUAD_STRIP);
      for (i = 0; i < npoints; i++)
        {
          glVertex3f (pointsx0[i], pointsy0[i], thick2);
          glVertex3f (pointsx1[i], pointsy1[i], thick2);
        }
      glEnd();

      /* inside edge */
      glFrontFace(GL_CW);
      glBegin (GL_QUAD_STRIP);
      for (i = 0; i < npoints; i++)
        {
          glNormal3f (-pointsx0[i], -pointsy0[i],  0);
          glVertex3f ( pointsx0[i],  pointsy0[i],  thick2);
          glVertex3f ( pointsx0[i],  pointsy0[i], -thick2);
        }
      glEnd();

      /* outside edge */
      glFrontFace(GL_CCW);
      glBegin (GL_QUADS);
      {
        for (i = 0; i < npoints-1; i++)
          {
            int ia = (i == 0 ? npoints-2 : i-1);
            int iz = (i == npoints-2 ? 0 : i+1);
            GLfloat  x = pointsx1[i];
            GLfloat  y = pointsy1[i];
            GLfloat xz = pointsx1[iz];
            GLfloat yz = pointsy1[iz];

            GLfloat nxa = normals[ia*2];   /* normal of [i-1 - i] face */
            GLfloat nya = normals[ia*2+1];
            GLfloat nx  = normals[i*2];    /* normal of [i - i+1] face */
            GLfloat ny  = normals[i*2+1];
            GLfloat nxz = normals[iz*2];    /* normal of [i+1 - i+2] face */
            GLfloat nyz = normals[iz*2+1];

            GLfloat anglea = vector_angle (nx, ny, 0, nxa, nya, 0);
            GLfloat anglez = vector_angle (nx, ny, 0, nxz, nyz, 0);
            GLfloat pointy = 0.005;

            if (anglea > pointy)
              {
                glNormal3f (nx, ny, 0);
                glVertex3f (x,  y,   thick2);
                glVertex3f (x,  y,  -thick2);
              }
            else
              {
                glNormal3f ((nxa + nx) / 2, (nya + ny) / 2, 0);
                glVertex3f (x,  y,   thick2);
                glVertex3f (x,  y,  -thick2);
              }

            if (anglez > pointy)
              {
                glNormal3f (nx, ny, 0);
                glVertex3f (xz, yz, -thick2);
                glVertex3f (xz, yz,  thick2);
              }
            else
              {
                glNormal3f ((nx + nxz) / 2, (ny + nyz) / 2, 0);
                glVertex3f (xz, yz, -thick2);
                glVertex3f (xz, yz,  thick2);
              }
          }
      }
      glEnd();
    }

  /* Fill in the upper left hole...
   */
  {
    GLfloat th;
    npoints = 0;

    th = 339.0 * d2r;
    pointsx0[npoints] = r1c * cos(th) * dc->gasket_size;
    pointsy0[npoints] = r1c * sin(th) * dc->gasket_size;
    npoints++;
    pointsx0[npoints] = r4 * cos(th) * dc->gasket_size;
    pointsy0[npoints] = r4 * sin(th) * dc->gasket_size;
    npoints++;

    th = 343.0 * d2r;
    pointsx0[npoints] = r1c * cos(th) * dc->gasket_size;
    pointsy0[npoints] = r1c * sin(th) * dc->gasket_size;
    npoints++;
    pointsx0[npoints] = r4 * cos(th) * dc->gasket_size;
    pointsy0[npoints] = r4 * sin(th) * dc->gasket_size;
    npoints++;

    if (! wire)
      {
        /* front wall */
        glNormal3f (0, 0, -1);
        glFrontFace(GL_CW);
        glBegin (wire ? GL_LINE_LOOP : GL_QUADS);
        glVertex3f (pointsx0[0], pointsy0[0], -thick2);
        glVertex3f (pointsx0[1], pointsy0[1], -thick2);
        glVertex3f (pointsx0[3], pointsy0[3], -thick2);
        glVertex3f (pointsx0[2], pointsy0[2], -thick2);
        glEnd();

        /* back wall */
        glNormal3f (0, 0, 1);
        glFrontFace(GL_CCW);
        glBegin (wire ? GL_LINE_LOOP : GL_QUADS);
        glVertex3f (pointsx0[0], pointsy0[0],  thick2);
        glVertex3f (pointsx0[1], pointsy0[1],  thick2);
        glVertex3f (pointsx0[3], pointsy0[3],  thick2);
        glVertex3f (pointsx0[2], pointsy0[2],  thick2);
        glEnd();
      }

    /* top wall */
    glFrontFace(GL_CW);
    glBegin (wire ? GL_LINE_LOOP : GL_QUADS);
    glNormal3f (pointsx0[1], pointsy0[1], 0);
    glVertex3f (pointsx0[1], pointsy0[1],  thick2);
    glNormal3f (pointsx0[3], pointsy0[3], 0);
    glVertex3f (pointsx0[3], pointsy0[3],  thick2);
    glVertex3f (pointsx0[3], pointsy0[3], -thick2);
    glNormal3f (pointsx0[1], pointsy0[1], 0);
    glVertex3f (pointsx0[1], pointsy0[1], -thick2);
    glEnd();


    /* Now make a donut.
     */
    {
      int nsteps = 12;
      GLfloat r0 = 0.026;
      GLfloat r1 = 0.060;
      GLfloat th, cth, sth;

      glPushMatrix ();

      th = ((339.0 + 343.0) / 2) * d2r;
      
      glTranslatef (r1b * cos(th) * dc->gasket_size,
                    r1b * sin(th) * dc->gasket_size,
                    0);

      npoints = 0;
      for (i = 0; i < nsteps; i++)
        {
          th = 2 * M_PI * i / nsteps;
          cth = cos (th) * dc->gasket_size;
          sth = sin (th) * dc->gasket_size;
          pointsx0[npoints] = r0 * cth;
          pointsy0[npoints] = r0 * sth;
          pointsx1[npoints] = r1 * cth;
          pointsy1[npoints] = r1 * sth;
          npoints++;
        }

      pointsx0[npoints] = pointsx0[0];
      pointsy0[npoints] = pointsy0[0];
      pointsx1[npoints] = pointsx1[0];
      pointsy1[npoints] = pointsy1[0];
      npoints++;

      if (wire)
        {
          glBegin (GL_LINE_LOOP);
          for (i = 0; i < npoints; i++)
            glVertex3f (pointsx0[i], pointsy0[i], -thick2);
          glEnd();
          glBegin (GL_LINE_LOOP);
          for (i = 0; i < npoints; i++)
            glVertex3f (pointsx0[i], pointsy0[i],  thick2);
          glEnd();
# if 0
          glBegin (GL_LINE_LOOP);
          for (i = 0; i < npoints; i++)
            glVertex3f (pointsx1[i], pointsy1[i], -thick2);
          glEnd();
          glBegin (GL_LINE_LOOP);
          for (i = 0; i < npoints; i++)
            glVertex3f (pointsx1[i], pointsy1[i],  thick2);
          glEnd();
# endif
        }
      else
        {
          /* top */
          glFrontFace(GL_CW);
          glNormal3f(0, 0, -1);
          glBegin (GL_QUAD_STRIP);
          for (i = 0; i < npoints; i++)
            {
              glVertex3f (pointsx0[i], pointsy0[i], -thick2);
              glVertex3f (pointsx1[i], pointsy1[i], -thick2);
            }
          glEnd();

          /* bottom */
          glFrontFace(GL_CCW);
          glNormal3f(0, 0, 1);
          glBegin (GL_QUAD_STRIP);
          for (i = 0; i < npoints; i++)
            {
              glVertex3f (pointsx0[i], pointsy0[i],  thick2);
              glVertex3f (pointsx1[i], pointsy1[i],  thick2);
            }
          glEnd();
        }

      /* inside edge */
      glFrontFace(GL_CW);
      glBegin (wire ? GL_LINES : GL_QUAD_STRIP);
      for (i = 0; i < npoints; i++)
        {
          glNormal3f (-pointsx0[i], -pointsy0[i],  0);
          glVertex3f ( pointsx0[i],  pointsy0[i],  thick2);
          glVertex3f ( pointsx0[i],  pointsy0[i], -thick2);
        }
      glEnd();

      glPopMatrix();
    }
  }


  /* Attach the bottom-right dingus...
   */
  {
    GLfloat w = 0.04;
    GLfloat h = 0.17;
    GLfloat th;

    glRotatef (50, 0, 0, 1);
    glScalef (dc->gasket_size, dc->gasket_size, 1);
    glTranslatef (0, (r0+r1)/2, 0);

    /* buried box */
    if (! wire)
      {
        glFrontFace(GL_CCW);
        glBegin (wire ? GL_LINE_STRIP : GL_QUADS);
        glNormal3f (0, 0, -1);
        glVertex3f (-w/2, -h/2, -thick2); glVertex3f (-w/2,  h/2, -thick2);
        glVertex3f ( w/2,  h/2, -thick2); glVertex3f ( w/2, -h/2, -thick2);
        glNormal3f (1, 0, 0);
        glVertex3f ( w/2, -h/2, -thick2); glVertex3f ( w/2,  h/2, -thick2);
        glVertex3f ( w/2,  h/2,  thick2); glVertex3f ( w/2, -h/2,  thick2);
        glNormal3f (0, 0, 1);
        glVertex3f ( w/2, -h/2,  thick2); glVertex3f ( w/2,  h/2,  thick2);
        glVertex3f (-w/2,  h/2,  thick2); glVertex3f (-w/2, -h/2,  thick2);
        glNormal3f (-1, 0, 0);
        glVertex3f (-w/2, -h/2,  thick2); glVertex3f (-w/2,  h/2,  thick2);
        glVertex3f (-w/2,  h/2, -thick2); glVertex3f (-w/2, -h/2, -thick2);
        glEnd();
      }

    npoints = 0;
    for (th = 0; th < M_PI; th += (M_PI / 6))
      {
        pointsx0[npoints] = w/2 * cos(th);
        pointsy0[npoints] = w/2 * sin(th);
        npoints++;
      }

    /* front inside curve */
    glNormal3f (0, 0, -1);
    glFrontFace(GL_CW);
    glBegin (wire ? GL_LINE_STRIP : GL_TRIANGLE_FAN);
    if (! wire) glVertex3f (0, h/2, -thick2);
    for (i = 0; i < npoints; i++)
      glVertex3f (pointsx0[i], h/2 + pointsy0[i], -thick2);
    glEnd();

    /* front outside curve */
    glFrontFace(GL_CCW);
    glBegin (wire ? GL_LINE_STRIP : GL_TRIANGLE_FAN);
    if (! wire) glVertex3f (0, -h/2, -thick2);
    for (i = 0; i < npoints; i++)
      glVertex3f (pointsx0[i], -h/2 - pointsy0[i], -thick2);
    glEnd();

    /* back inside curve */
    glNormal3f (0, 0, 1);
    glFrontFace(GL_CCW);
    glBegin (wire ? GL_LINE_STRIP : GL_TRIANGLE_FAN);
    if (! wire) glVertex3f (0, h/2, thick2);
    for (i = 0; i < npoints; i++)
      glVertex3f (pointsx0[i], h/2 + pointsy0[i], thick2);
    glEnd();

    /* back outside curve */
    glFrontFace(GL_CW);
    glBegin (wire ? GL_LINE_STRIP : GL_TRIANGLE_FAN);
    if (! wire) glVertex3f (0, -h/2, thick2);
    for (i = 0; i < npoints; i++)
      glVertex3f (pointsx0[i], -h/2 - pointsy0[i], thick2);
    glEnd();

    /* inside curve */
    glFrontFace(GL_CCW);
    glBegin (wire ? GL_LINES : GL_QUAD_STRIP);
    for (i = 0; i < npoints; i++)
      {
        glNormal3f (pointsx0[i], pointsy0[i], 0);
        glVertex3f (pointsx0[i], h/2 + pointsy0[i],  thick2);
        glVertex3f (pointsx0[i], h/2 + pointsy0[i], -thick2);
      }
    glEnd();

    /* outside curve */
    glFrontFace(GL_CW);
    glBegin (wire ? GL_LINES : GL_QUAD_STRIP);
    for (i = 0; i < npoints; i++)
      {
        glNormal3f (pointsx0[i], -pointsy0[i], 0);
        glVertex3f (pointsx0[i], -h/2 - pointsy0[i],  thick2);
        glVertex3f (pointsx0[i], -h/2 - pointsy0[i], -thick2);
      }
    glEnd();
  }

  free (pointsx0);
  free (pointsy0);
  free (pointsx1);
  free (pointsy1);
  free (normals);

  glPopMatrix();
}