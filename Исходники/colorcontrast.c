/** process, all real work is done here. */
void process (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, void *i, void *o, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  // this is called for preview and full pipe separately, each with its own pixelpipe piece.
  assert(dt_iop_module_colorspace(self) == iop_cs_Lab);
  // get our data struct:
  dt_iop_colorcontrast_params_t *d = (dt_iop_colorcontrast_params_t *)piece->data;
  // how many colors in our buffer?
  const int ch = piece->colors;
  // iterate over all output pixels (same coordinates as input)
#ifdef _OPENMP
  // optional: parallelize it!
  #pragma omp parallel for default(none) schedule(static) shared(i,o,roi_in,roi_out,d)
#endif
  for(int j=0; j<roi_out->height; j++)
  {

    float *in  = ((float *)i) + ch*roi_in->width *j;
    float *out = ((float *)o) + ch*roi_out->width*j;

    const __m128 scale = _mm_set_ps(0.0f,d->b_steepness,d->a_steepness,1.0f);
    const __m128 offset = _mm_set_ps(0.0f,d->b_offset,d->a_offset,0.0f);
    const __m128 min = _mm_set_ps(0.0f,-128.0f,-128.0f, -INFINITY);
    const __m128 max = _mm_set_ps(0.0f, 128.0f, 128.0f,  INFINITY);


    for(int i=0; i<roi_out->width; i++)
    {
      _mm_stream_ps(out,_mm_min_ps(max,_mm_max_ps(min,_mm_add_ps(offset,_mm_mul_ps(scale,_mm_load_ps(in))))));
      in+=ch;
      out+=ch;
    }
  }
  _mm_sfence();
}