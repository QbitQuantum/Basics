void
commit_params (dt_iop_module_t *self, dt_iop_params_t *p1, dt_dev_pixelpipe_t *pipe, dt_dev_pixelpipe_iop_t *piece)
{
  dt_iop_profilegamma_params_t *p = (dt_iop_profilegamma_params_t *)p1;
  dt_iop_profilegamma_data_t *d = (dt_iop_profilegamma_data_t *)piece->data;

  const float linear = p->linear;
  const float gamma  = p->gamma;

  d->linear = p->linear;
  d->gamma  = p->gamma;

  float a, b, c, g;
  if(gamma == 1.0)
  {
#ifdef _OPENMP
    #pragma omp parallel for default(none) shared(d) schedule(static)
#endif
    for(int k=0; k<0x10000; k++) d->table[k] = 1.0*k/0x10000;
  }
  else
  {
    if(linear == 0.0)
    {
#ifdef _OPENMP
      #pragma omp parallel for default(none) shared(d) schedule(static)
#endif
      for(int k=0; k<0x10000; k++)
        d->table[k] = powf(1.00*k/0x10000, gamma);
    }
    else
    {
      if(linear<1.0)
      {
        g = gamma*(1.0-linear)/(1.0-gamma*linear);
        a = 1.0/(1.0+linear*(g-1));
        b = linear*(g-1)*a;
        c = powf(a*linear+b, g)/linear;
      }
      else
      {
        a = b = g = 0.0;
        c = 1.0;
      }
#ifdef _OPENMP
      #pragma omp parallel for default(none) shared(d,a,b,c,g) schedule(static)
#endif
      for(int k=0; k<0x10000; k++)
      {
        float tmp;
        if (k<0x10000*linear) tmp = c*k/0x10000;
        else tmp = powf(a*k/0x10000+b, g);
        d->table[k] = tmp;
      }
    }
  }

  // now the extrapolation stuff:
  const float x[4] = {0.7f, 0.8f, 0.9f, 1.0f};
  const float y[4] = {d->table[CLAMP((int)(x[0]*0x10000ul), 0, 0xffff)],
    d->table[CLAMP((int)(x[1]*0x10000ul), 0, 0xffff)],
    d->table[CLAMP((int)(x[2]*0x10000ul), 0, 0xffff)],
    d->table[CLAMP((int)(x[3]*0x10000ul), 0, 0xffff)]
  };
  dt_iop_estimate_exp(x, y, 4, d->unbounded_coeffs);
}