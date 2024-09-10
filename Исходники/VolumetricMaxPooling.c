static void THNN_(VolumetricMaxPooling_updateOutput_frame)(
  real *input_p, real *output_p, real *indz_p,
  long nslices, long itime, long iwidth, long iheight,
  long otime, long owidth, long oheight,
  int kT, int kW, int kH,
  int dT, int dW, int dH,
  int pT, int pW, int pH)
{
  long k;
#pragma omp parallel for private(k)
  for (k = 0; k < nslices; k++)
  {
    /* loop over output */
    long i, j, ti;
    for (ti = 0; ti < otime; ti++)
    {
      for (i = 0; i < oheight; i++)
      {
        for (j = 0; j < owidth; j++)
        {
          /* local pointers */

          long start_t = ti * dT - pT;
          long start_h = i * dH - pH;
          long start_w = j * dW - pW;

          long kernel_t = fminf(kT, kT + start_t);
          long kernel_h = fminf(kH, kH + start_h);
          long kernel_w = fminf(kW, kW + start_w);

          start_t = fmaxf(start_t, 0);
          start_h = fmaxf(start_h, 0);
          start_w = fmaxf(start_w, 0);

          real *ip = input_p + k * itime * iwidth * iheight
            + start_t * iwidth * iheight + start_h * iwidth + start_w;
          real *op = output_p + k * otime * owidth * oheight
            + ti * owidth * oheight + i * owidth + j;
          real *indzp = indz_p + k * otime * owidth * oheight
            + ti * owidth * oheight + i * owidth + j;

          /* compute local max: */
          real maxval = -THInf;
          int x,y,z;
          int mx, my, mz;

          for (z = 0; z < kernel_t; z++)
          {
            for (y = 0; y < kernel_h; y++)
            {
              for (x = 0; x < kernel_w; x++)
              {
                if ((start_t + z < itime) && (start_h + y < iheight) && (start_w + x < iwidth))
                {
                  real val = *(ip + z * iwidth * iheight + y * iwidth + x);
                  if (val > maxval)
                  {
                    maxval = val;
                    // Store indices w.r.t the kernel dimension
                    mz = z + (kT - kernel_t);
                    my = y + (kH - kernel_h);
                    mx = x + (kW - kernel_w);
                  }
                }
              }
            }
          }

          // set max values
          ((unsigned char*)(indzp))[0] = mz;
          ((unsigned char*)(indzp))[1] = my;
          ((unsigned char*)(indzp))[2] = mx;
          ((unsigned char*)(indzp))[3] = 0;

          /* set output to local max */
          *op = maxval;
        }
      }
    }
  }
}