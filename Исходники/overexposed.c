void
process (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, const void * const ivoid, void *ovoid, const dt_iop_roi_t *roi_in, const dt_iop_roi_t * const roi_out)
{
  dt_develop_t *dev = self->dev;

  const int ch = piece->colors;

  // FIXME: turn off the module instead?
  if(!dev->overexposed.enabled || !dev->gui_attached)
  {
    memcpy(ovoid, ivoid, (size_t)roi_out->width*roi_out->height*sizeof(float)*ch);
    return;
  }

  const __m128 upper = _mm_set_ps(FLT_MAX,
                                  dev->overexposed.upper / 100.0f,
                                  dev->overexposed.upper / 100.0f,
                                  dev->overexposed.upper / 100.0f);
  const __m128 lower = _mm_set_ps(FLT_MAX,
                                  dev->overexposed.lower / 100.0f,
                                  dev->overexposed.lower / 100.0f,
                                  dev->overexposed.lower / 100.0f);

  const int colorscheme = dev->overexposed.colorscheme;
  const __m128 upper_color = _mm_load_ps(dt_iop_overexposed_colors[colorscheme][0]);
  const __m128 lower_color = _mm_load_ps(dt_iop_overexposed_colors[colorscheme][1]);

#ifdef _OPENMP
  #pragma omp parallel for default(none) shared(ovoid) schedule(static)
#endif
  for(int k=0; k<roi_out->height; k++)
  {
    const float *in = ((float *)ivoid) + (size_t)ch*k*roi_out->width;
    float *out = ((float *)ovoid) + (size_t)ch*k*roi_out->width;

    for (int j=0; j<roi_out->width; j++,in+=4,out+=4)
    {
      const __m128 pixel = _mm_load_ps(in);

      __m128 isoe = _mm_cmpge_ps(pixel, upper);
      isoe = _mm_or_ps(_mm_unpacklo_ps(isoe, isoe), _mm_unpackhi_ps(isoe, isoe));
      isoe = _mm_or_ps(_mm_unpacklo_ps(isoe, isoe), _mm_unpackhi_ps(isoe, isoe));

      __m128 isue = _mm_cmple_ps(pixel, lower);
      isue = _mm_and_ps(_mm_unpacklo_ps(isue, isue), _mm_unpackhi_ps(isue, isue));
      isue = _mm_and_ps(_mm_unpacklo_ps(isue, isue), _mm_unpackhi_ps(isue, isue));

      __m128 result = _mm_or_ps(_mm_andnot_ps(isoe, pixel),
                                _mm_and_ps(isoe, upper_color));

      result = _mm_or_ps(_mm_andnot_ps(isue, result),
                         _mm_and_ps(isue, lower_color));

      _mm_stream_ps(out, result);
    }
  }
  _mm_sfence();

  if(piece->pipe->mask_display)
    dt_iop_alpha_copy(ivoid, ovoid, roi_out->width, roi_out->height);
}