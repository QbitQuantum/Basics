void process (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, void *ivoid, void *ovoid, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  dt_iop_relight_data_t *data = (dt_iop_relight_data_t *)piece->data;
  const int ch = piece->colors;

  // Precalculate parameters for gauss function
  const float a = 1.0;                                                                // Height of top
  const float b = -1.0+(data->center*2);                                 // Center of top
  const float c = (data->width/10.0)/2.0;      				                    // Width

#ifdef _OPENMP
  #pragma omp parallel for default(none) shared(roi_out, ivoid, ovoid, data) schedule(static)
#endif
  for(int k=0; k<roi_out->height; k++)
  {
    float *in = ((float *)ivoid) + ch*k*roi_out->width;
    float *out = ((float *)ovoid) + ch*k*roi_out->width;
    for(int j=0; j<roi_out->width; j++,in+=ch,out+=ch)
    {
      const float lightness = in[0]/100.0;
      const float x = -1.0+(lightness*2.0);
      float gauss = GAUSS(a,b,c,x);

      if(isnan(gauss) || isinf(gauss))
        gauss = 0.0;

      float relight = 1.0 / exp2f ( -data->ev * CLIP(gauss));

      if(isnan(relight) || isinf(relight))
        relight = 1.0;

      out[0] = 100.0*CLIP (lightness*relight);
      out[1] = in[1];
      out[2] = in[2];
      out[3] = in[3];
    }
  }
}