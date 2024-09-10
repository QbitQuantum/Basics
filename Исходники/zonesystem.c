void process (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, void *ivoid, void *ovoid, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  float *in;
  float *out;
  dt_iop_zonesystem_gui_data_t *g = NULL;
  dt_iop_zonesystem_data_t *data = (dt_iop_zonesystem_data_t*)piece->data;

  guchar *buffer = NULL;
  if( self->dev->gui_attached && piece->pipe->type == DT_DEV_PIXELPIPE_PREVIEW )
  {
    g = (dt_iop_zonesystem_gui_data_t *)self->gui_data;
    dt_pthread_mutex_lock(&g->lock);
    if(g->preview_buffer)
      g_free (g->preview_buffer);

    buffer = g->preview_buffer = g_malloc (roi_in->width*roi_in->height);
    g->preview_width=roi_out->width;
    g->preview_height=roi_out->height;
  }

  /* calculate zonemap */
  const int size = data->size;
  float zonemap[MAX_ZONE_SYSTEM_SIZE]= {-1};
  _iop_zonesystem_calculate_zonemap (data, zonemap);
  const int ch = piece->colors;

  /* if gui and have buffer lets gaussblur and fill buffer with zone indexes */
  if( self->dev->gui_attached && g && buffer)
  {
    /* setup gaussian kernel */
    const int radius = 8;
    const int rad = MIN(radius, ceilf(radius * roi_in->scale / piece->iscale));
    const int wd = 2*rad+1;
    float mat[wd*wd];
    float *m;
    const float sigma2 = (2.5*2.5)*(radius*roi_in->scale/piece->iscale)*(radius*roi_in->scale/piece->iscale);
    float weight = 0.0f;

    memset(mat, 0, wd*wd*sizeof(float));

    m = mat;
    for(int l=-rad; l<=rad; l++) for(int k=-rad; k<=rad; k++,m++)
        weight += *m = expf(- (l*l + k*k)/(2.f*sigma2));
    m = mat;
    for(int l=-rad; l<=rad; l++) for(int k=-rad; k<=rad; k++,m++)
        *m /= weight;

    /* gauss blur the L channel */
#ifdef _OPENMP
    #pragma omp parallel for default(none) private(in, out, m) shared(mat, ivoid, ovoid, roi_out, roi_in) schedule(static)
#endif
    for(int j=rad; j<roi_out->height-rad; j++)
    {
      in  = ((float *)ivoid) + ch*(j*roi_in->width  + rad);
      out = ((float *)ovoid) + ch*(j*roi_out->width + rad);
      for(int i=rad; i<roi_out->width-rad; i++)
      {
        for(int c=0; c<3; c++) out[c] = 0.0f;
        float sum = 0.0;
        m = mat;
        for(int l=-rad; l<=rad; l++)
        {
          float *inrow = in + ch*(l*roi_in->width-rad);
          for(int k=-rad; k<=rad; k++,inrow+=ch,m++)
            sum += *m * inrow[0];
        }
        out[0] = sum;
        out += ch;
        in += ch;
      }
    }

    /* create zonemap preview */
//     in  = (float *)ivoid;
    out = (float *)ovoid;
#ifdef _OPENMP
    #pragma omp parallel for default(none) shared(roi_out,out,buffer,g,zonemap) schedule(static)
#endif
    for (int k=0; k<roi_out->width*roi_out->height; k++)
    {
      buffer[k] = _iop_zonesystem_zone_index_from_lightness (out[ch*k]/100.0f, zonemap, size);
    }

    dt_pthread_mutex_unlock(&g->lock);
  }

  /* process the image */
  in  = (float *)ivoid;
  out = (float *)ovoid;

  const float rzscale = (size-1)/100.0f;

  float zonemap_offset[MAX_ZONE_SYSTEM_SIZE]= {-1};
  float zonemap_scale[MAX_ZONE_SYSTEM_SIZE]= {-1};

  // precompute scale and offset
  for (int k=0; k < size-1; k++) zonemap_scale[k]  = (zonemap[k+1]-zonemap[k])*(size-1);
  for (int k=0; k < size-1; k++) zonemap_offset[k] = 100.0f * ((k+1)*zonemap[k] - k*zonemap[k+1]) ;

#ifdef _OPENMP
  #pragma omp parallel for default(none) shared(roi_out, in, out, zonemap_scale,zonemap_offset) schedule(static)
#endif
  for (int j=0; j<roi_out->height; j++)
    for (int i=0; i<roi_out->width; i++)
    {
      /* remap lightness into zonemap and apply lightness */
      const float *inp = in + ch*(j*roi_out->width+i);
      float *outp = out + ch*(j*roi_out->width+i);

      const int rz = CLAMPS(inp[0]*rzscale, 0, size-2);  // zone index

      const float zs = ((rz > 0) ? (zonemap_offset[rz]/inp[0]) : 0) + zonemap_scale[rz];

      _mm_stream_ps(outp,_mm_mul_ps(_mm_load_ps(inp),_mm_set1_ps(zs)));
    }

  _mm_sfence();

  if(piece->pipe->mask_display)
    dt_iop_alpha_copy(ivoid, ovoid, roi_out->width, roi_out->height);
}