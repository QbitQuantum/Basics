gboolean
gimp_operation_normal_process_sse2 (GeglOperation       *op,
                                    void                *in_p,
                                    void                *layer_p,
                                    void                *mask_p,
                                    void                *out_p,
                                    glong                samples,
                                    const GeglRectangle *roi,
                                    gint                 level)
{
  /* check alignment */
  if ((((uintptr_t)in_p) | ((uintptr_t)layer_p) | ((uintptr_t)out_p)) & 0x0F)
    {
      return gimp_operation_normal_process (op,
                                            in_p, layer_p, mask_p, out_p,
                                            samples, roi, level);
    }
  else
    {
      GimpOperationLayerMode *layer_mode      = (gpointer) op;
      gfloat                  opacity         = layer_mode->opacity;
      gfloat                 *mask            = mask_p;
      const                   __v4sf *v_in    = (const __v4sf*) in_p;
      const                   __v4sf *v_layer = (const __v4sf*) layer_p;
                              __v4sf *v_out   = (      __v4sf*) out_p;

      const __v4sf one       = _mm_set1_ps (1.0f);
      const __v4sf v_opacity = _mm_set1_ps (opacity);

      switch (layer_mode->real_composite_mode)
        {
        case GIMP_LAYER_COMPOSITE_UNION:
        case GIMP_LAYER_COMPOSITE_AUTO:
          while (samples--)
            {
              __v4sf rgba_in, rgba_layer, alpha;

              rgba_in    = *v_in++;
              rgba_layer = *v_layer++;

              /* expand alpha */
              alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_layer,
                                                 _MM_SHUFFLE (3, 3, 3, 3));

              if (mask)
                {
                  __v4sf mask_alpha;

                  /* multiply layer's alpha by the mask */
                  mask_alpha = _mm_set1_ps (*mask++);
                  alpha = alpha * mask_alpha;
                }

              alpha = alpha * v_opacity;

              if (_mm_ucomigt_ss (alpha, _mm_setzero_ps ()))
                {
                  __v4sf dst_alpha, a_term, out_pixel, out_alpha, out_pixel_rbaa;

                  /* expand alpha */
                  dst_alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_in,
                                                         _MM_SHUFFLE (3, 3, 3, 3));

                  /* a_term = dst_a * (1.0 - src_a) */
                  a_term = dst_alpha * (one - alpha);

                  /* out(color) = src * src_a + dst * a_term */
                  out_pixel = rgba_layer * alpha + rgba_in * a_term;

                  /* out(alpha) = 1.0 * src_a + 1.0 * a_term */
                  out_alpha = alpha + a_term;

                  /* un-premultiply */
                  out_pixel = out_pixel / out_alpha;

                  /* swap in the real alpha */
                  out_pixel_rbaa = _mm_shuffle_ps (out_pixel, out_alpha, _MM_SHUFFLE (3, 3, 2, 0));
                  out_pixel = _mm_shuffle_ps (out_pixel, out_pixel_rbaa, _MM_SHUFFLE (2, 1, 1, 0));

                  *v_out++ = out_pixel;
                }
              else
                {
                  *v_out++ = rgba_in;
                }
            }
          break;

        case GIMP_LAYER_COMPOSITE_CLIP_TO_BACKDROP:
          while (samples--)
            {
              __v4sf rgba_in, rgba_layer, alpha;

              rgba_in    = *v_in++;
              rgba_layer = *v_layer++;

              /* expand alpha */
              alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_layer,
                                                 _MM_SHUFFLE (3, 3, 3, 3));

              if (mask)
                {
                  __v4sf mask_alpha;

                  /* multiply layer's alpha by the mask */
                  mask_alpha = _mm_set1_ps (*mask++);
                  alpha = alpha * mask_alpha;
                }

              alpha = alpha * v_opacity;

              if (_mm_ucomigt_ss (alpha, _mm_setzero_ps ()))
                {
                  __v4sf dst_alpha, out_pixel, out_pixel_rbaa;

                  /* expand alpha */
                  dst_alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_in,
                                                         _MM_SHUFFLE (3, 3, 3, 3));

                  /* out(color) = dst * (1 - src_a) + src * src_a */
                  out_pixel = rgba_in + (rgba_layer - rgba_in) * alpha;

                  /* swap in the real alpha */
                  out_pixel_rbaa = _mm_shuffle_ps (out_pixel, dst_alpha, _MM_SHUFFLE (3, 3, 2, 0));
                  out_pixel = _mm_shuffle_ps (out_pixel, out_pixel_rbaa, _MM_SHUFFLE (2, 1, 1, 0));

                  *v_out++ = out_pixel;
                }
              else
                {
                  *v_out++ = rgba_in;
                }
            }
          break;

        case GIMP_LAYER_COMPOSITE_CLIP_TO_LAYER:
          while (samples--)
            {
              __v4sf rgba_in, rgba_layer, alpha;
              __v4sf out_pixel, out_pixel_rbaa;

              rgba_in    = *v_in++;
              rgba_layer = *v_layer++;

              /* expand alpha */
              alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_layer,
                                                 _MM_SHUFFLE (3, 3, 3, 3));

              if (mask)
                {
                  __v4sf mask_alpha;

                  /* multiply layer's alpha by the mask */
                  mask_alpha = _mm_set1_ps (*mask++);
                  alpha = alpha * mask_alpha;
                }

              alpha = alpha * v_opacity;

              if (_mm_ucomigt_ss (alpha, _mm_setzero_ps ()))
                {
                  /* out(color) = src */
                  out_pixel = rgba_layer;
                }
              else
                {
                  out_pixel = rgba_in;
                }

              /* swap in the real alpha */
              out_pixel_rbaa = _mm_shuffle_ps (out_pixel, alpha, _MM_SHUFFLE (3, 3, 2, 0));
              out_pixel = _mm_shuffle_ps (out_pixel, out_pixel_rbaa, _MM_SHUFFLE (2, 1, 1, 0));

              *v_out++ = out_pixel;
            }
          break;

        case GIMP_LAYER_COMPOSITE_INTERSECTION:
          while (samples--)
            {
              __v4sf rgba_in, rgba_layer, alpha;
              __v4sf out_pixel, out_pixel_rbaa;

              rgba_in    = *v_in++;
              rgba_layer = *v_layer++;

              /* expand alpha */
              alpha = (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_layer,
                                                 _MM_SHUFFLE (3, 3, 3, 3));

              if (mask)
                {
                  __v4sf mask_alpha;

                  /* multiply layer's alpha by the mask */
                  mask_alpha = _mm_set1_ps (*mask++);
                  alpha = alpha * mask_alpha;
                }

              alpha = alpha * v_opacity;

              /* multiply the alpha by in's alpha */
              alpha *= (__v4sf)_mm_shuffle_epi32 ((__m128i)rgba_in,
                                                  _MM_SHUFFLE (3, 3, 3, 3));

              if (_mm_ucomigt_ss (alpha, _mm_setzero_ps ()))
                {
                  /* out(color) = src */
                  out_pixel = rgba_layer;
                }
              else
                {
                  out_pixel = rgba_in;
                }

              /* swap in the real alpha */
              out_pixel_rbaa = _mm_shuffle_ps (out_pixel, alpha, _MM_SHUFFLE (3, 3, 2, 0));
              out_pixel = _mm_shuffle_ps (out_pixel, out_pixel_rbaa, _MM_SHUFFLE (2, 1, 1, 0));

              *v_out++ = out_pixel;
            }
          break;
        }
    }

  return TRUE;
}