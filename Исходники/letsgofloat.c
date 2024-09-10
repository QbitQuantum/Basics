void
process(
  struct dt_iop_module_t *self,
  dt_dev_pixelpipe_iop_t *piece,
  const void *const ivoid,
  void *ovoid,
  const dt_iop_roi_t *const roi_in,
  const dt_iop_roi_t *const roi_out)
{
  const  float divider  = (float)UINT16_MAX;
  const __m128 dividers = _mm_set_ps1(divider);

#ifdef _OPENMP
  #pragma omp parallel for default(none) schedule(static) shared(ovoid)
#endif
  for(int j = 0; j < roi_out->height; j++)
  {
    const uint16_t *in = ((uint16_t *)ivoid) + (size_t)j * roi_out->width;
    float *out = ((float *)ovoid) + (size_t)j * roi_out->width;

    int i = 0;
    int alignment = ((8 - (j * roi_out->width & (8 - 1))) & (8 - 1));

    // process unaligned pixels
    for ( ; i < alignment ; i++, out++, in++)
      *out = ((float)(*in)) / divider;

    // process aligned pixels with SSE
    for( ; i < roi_out->width - (8 - 1); i += 8, in += 8)
    {
      const __m128i input = _mm_load_si128((__m128i *)in);

      __m128i ilo = _mm_unpacklo_epi16(input, _mm_set1_epi16(0));
      __m128i ihi = _mm_unpackhi_epi16(input, _mm_set1_epi16(0));

      __m128 flo = _mm_cvtepi32_ps(ilo);
      __m128 fhi = _mm_cvtepi32_ps(ihi);

      flo = _mm_div_ps(flo, dividers);
      fhi = _mm_div_ps(fhi, dividers);

      _mm_stream_ps(out, flo);
      out += 4;
      _mm_stream_ps(out, fhi);
      out += 4;
    }

    // process the rest
    for( ; i < roi_out->width; i++, out++, in++)
      *out = ((float)(*in)) / divider;
  }
  _mm_sfence();
}