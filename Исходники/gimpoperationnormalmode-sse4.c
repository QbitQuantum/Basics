gboolean
gimp_operation_normal_mode_process_pixels_sse4 (gfloat              *in,
                                                gfloat              *aux,
                                                gfloat              *mask,
                                                gfloat              *out,
                                                gfloat               opacity,
                                                glong                samples,
                                                const GeglRectangle *roi,
                                                gint                 level)
{
  /* check alignment */
  if ((((uintptr_t)in) | ((uintptr_t)aux) | ((uintptr_t)out)) & 0x0F)
    {
      return gimp_operation_normal_mode_process_pixels_core (in, aux, mask, out,
                                                             opacity, samples,
                                                             roi, level);
    }
  else
    {
      const __v4sf *v_in  = (const __v4sf*) in;
      const __v4sf *v_aux = (const __v4sf*) aux;
            __v4sf *v_out = (      __v4sf*) out;

      const __v4sf one = _mm_set1_ps (1.0f);
      const __v4sf v_opacity = _mm_set1_ps (opacity);

      while (samples--)
        {
          __v4sf rgba_in, rgba_aux, alpha;

          rgba_in  = *v_in++;
          rgba_aux = *v_aux++;

          /* expand alpha */
          alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_aux,
                                             _MM_SHUFFLE (3, 3, 3, 3));

          if (mask)
            {
              __v4sf mask_alpha;

              /* multiply aux's alpha by the mask */
              mask_alpha = _mm_set1_ps (*mask++);
              alpha = alpha * mask_alpha;
            }

          alpha = alpha * v_opacity;

          if (_mm_ucomigt_ss (alpha, _mm_setzero_ps ()))
            {
              __v4sf dst_alpha, a_term, out_pixel, out_alpha;

              /* expand alpha */
              dst_alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_in,
                                                     _MM_SHUFFLE (3, 3, 3, 3));

              /* a_term = dst_a * (1.0 - src_a) */
              a_term = dst_alpha * (one - alpha);

              /* out(color) = src * src_a + dst * a_term */
              out_pixel = rgba_aux * alpha + rgba_in * a_term;

              /* out(alpha) = 1.0 * src_a + 1.0 * a_term */
              out_alpha = alpha + a_term;

              /* un-premultiply */
              out_pixel = out_pixel / out_alpha;

              /* swap in the real alpha */
              out_pixel = _mm_blend_ps (out_pixel, out_alpha, 0x08);

              *v_out++ = out_pixel;
            }
          else
            {
              *v_out++ = rgba_in;
            }
        }
    }

  return TRUE;
}