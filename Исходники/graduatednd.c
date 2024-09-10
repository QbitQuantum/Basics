void process_sse2(struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, void *ivoid, void *ovoid,
                  const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  const dt_iop_graduatednd_data_t *data = (dt_iop_graduatednd_data_t *)piece->data;
  const int ch = piece->colors;

  const int ix = (roi_in->x);
  const int iy = (roi_in->y);
  const float iw = piece->buf_in.width * roi_out->scale;
  const float ih = piece->buf_in.height * roi_out->scale;
  const float hw = iw / 2.0;
  const float hh = ih / 2.0;
  const float hw_inv = 1.0 / hw;
  const float hh_inv = 1.0 / hh;
  const float v = (-data->rotation / 180) * M_PI;
  const float sinv = sin(v);
  const float cosv = cos(v);
  const float filter_radie = sqrt((hh * hh) + (hw * hw)) / hh;
  const float offset = data->offset / 100.0 * 2;

  float color[3];
  hsl2rgb(color, data->hue, data->saturation, 0.5);
  if(data->density < 0)
    for(int l = 0; l < 3; l++) color[l] = 1.0 - color[l];

#if 1
  const float filter_compression = 1.0 / filter_radie
                                   / (1.0 - (0.5 + (data->compression / 100.0) * 0.9 / 2.0)) * 0.5;
#else
  const float compression = data->compression / 100.0f;
  const float t = 1.0f - .8f / (.8f + compression);
  const float c = 1.0f + 1000.0f * powf(4.0, compression);
#endif


  if(data->density > 0)
  {
#ifdef _OPENMP
#pragma omp parallel for default(none) shared(roi_out, color, data, ivoid, ovoid) schedule(static)
#endif
    for(int y = 0; y < roi_out->height; y++)
    {
      size_t k = (size_t)roi_out->width * y * ch;
      const float *in = (float *)ivoid + k;
      float *out = (float *)ovoid + k;

      float length = (sinv * (-1.0 + ix * hw_inv) - cosv * (-1.0 + (iy + y) * hh_inv) - 1.0 + offset)
                     * filter_compression;
      const float length_inc = sinv * hw_inv * filter_compression;

      __m128 c = _mm_set_ps(0, color[2], color[1], color[0]);
      __m128 c1 = _mm_sub_ps(_mm_set1_ps(1.0f), c);

      for(int x = 0; x < roi_out->width; x++, in += ch, out += ch)
      {
#if 1
        // !!! approximation is ok only when highest density is 8
        // for input x = (data->density * CLIP( 0.5+length ), calculate 2^x as (e^(ln2*x/8))^8
        // use exp2f approximation to calculate e^(ln2*x/8)
        // in worst case - density==8,CLIP(0.5-length) == 1.0 it gives 0.6% of error
        const float t = 0.693147181f /* ln2 */ * (data->density * CLIP(0.5f + length) / 8.0f);
        float d1 = t * t * 0.5f;
        float d2 = d1 * t * 0.333333333f;
        float d3 = d2 * t * 0.25f;
        float d = 1 + t + d1 + d2 + d3; /* taylor series for e^x till x^4 */
        // printf("%d %d  %f\n",y,x,d);
        __m128 density = _mm_set1_ps(d);
        density = _mm_mul_ps(density, density);
        density = _mm_mul_ps(density, density);
        density = _mm_mul_ps(density, density);
#else
        // use fair exp2f
        __m128 density = _mm_set1_ps(exp2f(data->density * CLIP(0.5f + length)));
#endif

        /* max(0,in / (c + (1-c)*density)) */
        _mm_stream_ps(out, _mm_max_ps(_mm_set1_ps(0.0f),
                                      _mm_div_ps(_mm_load_ps(in), _mm_add_ps(c, _mm_mul_ps(c1, density)))));

        length += length_inc;
      }
    }
  }
  else
  {
#ifdef _OPENMP
#pragma omp parallel for default(none) shared(roi_out, color, data, ivoid, ovoid) schedule(static)
#endif
    for(int y = 0; y < roi_out->height; y++)
    {
      size_t k = (size_t)roi_out->width * y * ch;
      const float *in = (float *)ivoid + k;
      float *out = (float *)ovoid + k;

      float length = (sinv * (-1.0f + ix * hw_inv) - cosv * (-1.0f + (iy + y) * hh_inv) - 1.0f + offset)
                     * filter_compression;
      const float length_inc = sinv * hw_inv * filter_compression;

      __m128 c = _mm_set_ps(0, color[2], color[1], color[0]);
      __m128 c1 = _mm_sub_ps(_mm_set1_ps(1.0f), c);

      for(int x = 0; x < roi_out->width; x++, in += ch, out += ch)
      {
#if 1
        // !!! approximation is ok only when lowest density is -8
        // for input x = (-data->density * CLIP( 0.5-length ), calculate 2^x as (e^(ln2*x/8))^8
        // use exp2f approximation to calculate e^(ln2*x/8)
        // in worst case - density==-8,CLIP(0.5-length) == 1.0 it gives 0.6% of error
        const float t = 0.693147181f /* ln2 */ * (-data->density * CLIP(0.5f - length) / 8.0f);
        float d1 = t * t * 0.5f;
        float d2 = d1 * t * 0.333333333f;
        float d3 = d2 * t * 0.25f;
        float d = 1 + t + d1 + d2 + d3; /* taylor series for e^x till x^4 */
        __m128 density = _mm_set1_ps(d);
        density = _mm_mul_ps(density, density);
        density = _mm_mul_ps(density, density);
        density = _mm_mul_ps(density, density);
#else
        __m128 density = _mm_set1_ps(exp2f(-data->density * CLIP(0.5f - length)));
#endif

        /* max(0,in * (c + (1-c)*density)) */
        _mm_stream_ps(out, _mm_max_ps(_mm_set1_ps(0.0f),
                                      _mm_mul_ps(_mm_load_ps(in), _mm_add_ps(c, _mm_mul_ps(c1, density)))));

        length += length_inc;
      }
    }
  }
  _mm_sfence();

  if(piece->pipe->mask_display) dt_iop_alpha_copy(ivoid, ovoid, roi_out->width, roi_out->height);
}