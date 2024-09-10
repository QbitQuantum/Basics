void process_sse2(dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, const void *const ivoid,
                  void *const ovoid, const dt_iop_roi_t *const roi_in, const dt_iop_roi_t *const roi_out)
{
  const dt_iop_rawprepare_data_t *const d = (dt_iop_rawprepare_data_t *)piece->data;

  // fprintf(stderr, "roi in %d %d %d %d\n", roi_in->x, roi_in->y, roi_in->width, roi_in->height);
  // fprintf(stderr, "roi out %d %d %d %d\n", roi_out->x, roi_out->y, roi_out->width, roi_out->height);

  const float scale = roi_in->scale / piece->iscale;
  const int csx = (int)roundf((float)d->x * scale), csy = (int)roundf((float)d->y * scale);

  if(!dt_dev_pixelpipe_uses_downsampled_input(piece->pipe) && piece->pipe->filters)
  { // raw mosaic
#ifdef _OPENMP
#pragma omp parallel for default(none) schedule(static)
#endif
    for(int j = 0; j < roi_out->height; j++)
    {
      const uint16_t *in = ((uint16_t *)ivoid) + ((size_t)roi_in->width * (j + csy) + csx);
      float *out = ((float *)ovoid) + (size_t)roi_out->width * j;

      int i = 0;

      // FIXME: figure alignment!  !!! replace with for !!!
      while((!dt_is_aligned(in, 16) || !dt_is_aligned(out, 16)) && (i < roi_out->width))
      {
        const int id = BL(roi_out, d, j, i);
        *out = (((float)(*in)) - d->sub[id]) / d->div[id];
        i++;
        in++;
        out++;
      }

      const __m128 sub = _mm_set_ps(d->sub[BL(roi_out, d, j, i + 3)], d->sub[BL(roi_out, d, j, i + 2)],
                                    d->sub[BL(roi_out, d, j, i + 1)], d->sub[BL(roi_out, d, j, i)]);

      const __m128 div = _mm_set_ps(d->div[BL(roi_out, d, j, i + 3)], d->div[BL(roi_out, d, j, i + 2)],
                                    d->div[BL(roi_out, d, j, i + 1)], d->div[BL(roi_out, d, j, i)]);

      // process aligned pixels with SSE
      for(; i < roi_out->width - (8 - 1); i += 8, in += 8)
      {
        const __m128i input = _mm_load_si128((__m128i *)in);

        __m128i ilo = _mm_unpacklo_epi16(input, _mm_set1_epi16(0));
        __m128i ihi = _mm_unpackhi_epi16(input, _mm_set1_epi16(0));

        __m128 flo = _mm_cvtepi32_ps(ilo);
        __m128 fhi = _mm_cvtepi32_ps(ihi);

        flo = _mm_div_ps(_mm_sub_ps(flo, sub), div);
        fhi = _mm_div_ps(_mm_sub_ps(fhi, sub), div);

        _mm_stream_ps(out, flo);
        out += 4;
        _mm_stream_ps(out, fhi);
        out += 4;
      }

      // process the rest
      for(; i < roi_out->width; i++, in++, out++)
      {
        const int id = BL(roi_out, d, j, i);
        *out = MAX(0.0f, ((float)(*in)) - d->sub[id]) / d->div[id];
      }
    }

    piece->pipe->filters = dt_rawspeed_crop_dcraw_filters(self->dev->image_storage.filters, csx, csy);
    adjust_xtrans_filters(piece->pipe, csx, csy);
  }
  else
  { // pre-downsampled buffer that needs black/white scaling

    const __m128 sub = _mm_load_ps(d->sub), div = _mm_load_ps(d->div);

#ifdef _OPENMP
#pragma omp parallel for default(none) schedule(static)
#endif
    for(int j = 0; j < roi_out->height; j++)
    {
      const float *in = ((float *)ivoid) + (size_t)4 * (roi_in->width * (j + csy) + csx);
      float *out = ((float *)ovoid) + (size_t)4 * roi_out->width * j;

      // process aligned pixels with SSE
      for(int i = 0; i < roi_out->width; i++, in += 4, out += 4)
      {
        const __m128 input = _mm_load_ps(in);

        const __m128 scaled = _mm_div_ps(_mm_sub_ps(input, sub), div);

        _mm_stream_ps(out, scaled);
      }
    }
  }
  _mm_sfence();
}