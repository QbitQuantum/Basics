void
process (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, void *ivoid, void *ovoid, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  const dt_iop_colorout_data_t *const d = (dt_iop_colorout_data_t *)piece->data;
  const int ch = piece->colors;
  const int gamutcheck = (d->softproof_enabled == DT_SOFTPROOF_GAMUTCHECK);

  if(!isnan(d->cmatrix[0]))
  {
    //fprintf(stderr,"Using cmatrix codepath\n");
    // convert to rgb using matrix
#ifdef _OPENMP
    #pragma omp parallel for schedule(static) default(none) shared(roi_in,roi_out, ivoid, ovoid)
#endif
    for(int j=0; j<roi_out->height; j++)
    {

      float *in  = (float*)ivoid + ch*roi_in->width *j;
      float *out = (float*)ovoid + ch*roi_out->width*j;
      const __m128 m0 = _mm_set_ps(0.0f,d->cmatrix[6],d->cmatrix[3],d->cmatrix[0]);
      const __m128 m1 = _mm_set_ps(0.0f,d->cmatrix[7],d->cmatrix[4],d->cmatrix[1]);
      const __m128 m2 = _mm_set_ps(0.0f,d->cmatrix[8],d->cmatrix[5],d->cmatrix[2]);

      for(int i=0; i<roi_out->width; i++, in+=ch, out+=ch )
      {
        const __m128 xyz = dt_Lab_to_XYZ_SSE(_mm_load_ps(in));
        const __m128 t = _mm_add_ps(_mm_mul_ps(m0,_mm_shuffle_ps(xyz,xyz,_MM_SHUFFLE(0,0,0,0))),_mm_add_ps(_mm_mul_ps(m1,_mm_shuffle_ps(xyz,xyz,_MM_SHUFFLE(1,1,1,1))),_mm_mul_ps(m2,_mm_shuffle_ps(xyz,xyz,_MM_SHUFFLE(2,2,2,2)))));

        _mm_stream_ps(out,t);
      }
    }
    _mm_sfence();
    // apply profile
#ifdef _OPENMP
    #pragma omp parallel for schedule(static) default(none) shared(roi_in,roi_out, ivoid, ovoid)
#endif
    for(int j=0; j<roi_out->height; j++)
    {

      float *in  = (float*)ivoid + ch*roi_in->width *j;
      float *out = (float*)ovoid + ch*roi_out->width*j;

      for(int i=0; i<roi_out->width; i++, in+=ch, out+=ch )
      {
        for(int i=0; i<3; i++)
          if (d->lut[i][0] >= 0.0f)
          {
            out[i] = (out[i] < 1.0f) ? lerp_lut(d->lut[i], out[i]) : dt_iop_eval_exp(d->unbounded_coeffs[i], out[i]);
          }
      }
    }
  }
  else
  {
    float *in  = (float*)ivoid;
    float *out = (float*)ovoid;
    const int rowsize=roi_out->width * 3;
    //fprintf(stderr,"Using xform codepath\n");

#ifdef _OPENMP
    #pragma omp parallel for schedule(static) default(none) shared(out, roi_out, in)
#endif
    for (int k=0; k<roi_out->height; k++)
    {
      float Lab[rowsize];
      float rgb[rowsize];

      const int m=(k*(roi_out->width*ch));
      for (int l=0; l<roi_out->width; l++)
      {
        int li=3*l,ii=ch*l;
        Lab[li+0] = in[m+ii+0];
        Lab[li+1] = in[m+ii+1];
        Lab[li+2] = in[m+ii+2];
      }

      cmsDoTransform (d->xform, Lab, rgb, roi_out->width);

      for (int l=0; l<roi_out->width; l++)
      {
        int oi=ch*l, ri=3*l;
        if(gamutcheck && (rgb[ri+0] < 0.0f || rgb[ri+1] < 0.0f || rgb[ri+2] < 0.0f))
        {
          out[m+oi+0] = 0.0f;
          out[m+oi+1] = 1.0f;
          out[m+oi+2] = 1.0f;
        }
        else
        {
          out[m+oi+0] = rgb[ri+0];
          out[m+oi+1] = rgb[ri+1];
          out[m+oi+2] = rgb[ri+2];
        }
      }
    }
  }

  if(piece->pipe->mask_display)
    dt_iop_alpha_copy(ivoid, ovoid, roi_out->width, roi_out->height);
}