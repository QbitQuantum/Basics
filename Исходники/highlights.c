void process (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, void *ivoid, void *ovoid, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  dt_iop_highlights_data_t *data = (dt_iop_highlights_data_t *)piece->data;
  float *in;
  float *out;
  const int ch = piece->colors;

  const float clip = data->clip * fminf(piece->pipe->processed_maximum[0], fminf(piece->pipe->processed_maximum[1], piece->pipe->processed_maximum[2]));
  float inc[3], lch[3], lchc[3], lchi[3];

  switch(data->mode)
  {
    case DT_IOP_HIGHLIGHTS_LCH:
#ifdef _OPENMP
      #pragma omp parallel for schedule(dynamic) default(none) shared(ovoid, ivoid, roi_out, data, piece) private(in, out, inc, lch, lchc, lchi)
#endif
      for(int j=0; j<roi_out->height; j++)
      {
        out = (float *)ovoid + ch*roi_out->width*j;
        in  = (float *)ivoid + ch*roi_out->width*j;
        for(int i=0; i<roi_out->width; i++)
        {
          if(in[0] <= clip && in[1] <= clip && in[2] <= clip)
          {
            // fast path for well-exposed pixels.
            for(int c=0; c<3; c++) out[c] = in[c];
          }
          else
          {
            for(int c=0; c<3; c++) inc[c] = fminf(clip, in[c]);
            rgb_to_lch(in, lchi);
            rgb_to_lch(inc, lchc);
            lch[0] = lchc[0] + data->blendL * (lchi[0] - lchc[0]);
            lch[1] = lchc[1] + data->blendC * (lchi[1] - lchc[1]);
            lch[2] = lchc[2] + data->blendh * (lchi[2] - lchc[2]);
            lch_to_rgb(lch, out);
          }
          out += ch;
          in += ch;
        }
      }
      break;
    default:
    case DT_IOP_HIGHLIGHTS_CLIP:
#ifdef _OPENMP
      #pragma omp parallel for schedule(dynamic) default(none) shared(ovoid, ivoid, roi_out) private(in, out, inc, lch, lchc, lchi)
#endif
      for(int j=0; j<roi_out->height; j++)
      {
        out = (float *)ovoid + ch*roi_out->width*j;
        in  = (float *)ivoid + ch*roi_out->width*j;
        for(int i=0; i<roi_out->width; i++)
        {
          for(int c=0; c<3; c++) out[c] = fminf(clip, in[c]);
          out += ch;
          in += ch;
        }
      }
      break;
  }

  if(piece->pipe->mask_display)
    dt_iop_alpha_copy(ivoid, ovoid, roi_out->width, roi_out->height);
}