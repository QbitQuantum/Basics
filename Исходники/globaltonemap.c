int process_cl(struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, cl_mem dev_in, cl_mem dev_out,
               const dt_iop_roi_t *const roi_in, const dt_iop_roi_t *const roi_out)
{
  dt_iop_global_tonemap_data_t *d = (dt_iop_global_tonemap_data_t *)piece->data;
  dt_iop_global_tonemap_global_data_t *gd = (dt_iop_global_tonemap_global_data_t *)self->data;
  dt_iop_global_tonemap_gui_data_t *g = (dt_iop_global_tonemap_gui_data_t *)self->gui_data;
  dt_bilateral_cl_t *b = NULL;

  cl_int err = -999;
  cl_mem dev_m = NULL;
  cl_mem dev_r = NULL;
  float *maximum = NULL;
  const int devid = piece->pipe->devid;
  int gtkernel = -1;

  const int width = roi_out->width;
  const int height = roi_out->height;
  float parameters[4] = { 0.0f };

  switch(d->operator)
  {
    case OPERATOR_REINHARD:
      gtkernel = gd->kernel_global_tonemap_reinhard;
      break;
    case OPERATOR_DRAGO:
      gtkernel = gd->kernel_global_tonemap_drago;
      break;
    case OPERATOR_FILMIC:
      gtkernel = gd->kernel_global_tonemap_filmic;
      break;
  }

  if(d->operator== OPERATOR_DRAGO)
  {
    const float eps = 0.0001f;
    float tmp_lwmax = NAN;

    // see comments in process() about lwmax value
    if(self->dev->gui_attached && g && piece->pipe->type == DT_DEV_PIXELPIPE_FULL)
    {
      dt_pthread_mutex_lock(&g->lock);
      const uint64_t hash = g->hash;
      dt_pthread_mutex_unlock(&g->lock);

      if(hash != 0 && !dt_dev_sync_pixelpipe_hash(self->dev, piece->pipe, 0, self->priority, &g->lock, &g->hash))
        dt_control_log(_("inconsistent output"));

      dt_pthread_mutex_lock(&g->lock);
      tmp_lwmax = g->lwmax;
      dt_pthread_mutex_unlock(&g->lock);
    }

    if(isnan(tmp_lwmax))
    {
      dt_opencl_local_buffer_t flocopt
        = (dt_opencl_local_buffer_t){ .xoffset = 0, .xfactor = 1, .yoffset = 0, .yfactor = 1,
                                      .cellsize = sizeof(float), .overhead = 0,
                                      .sizex = 1 << 4, .sizey = 1 << 4 };

      if(!dt_opencl_local_buffer_opt(devid, gd->kernel_pixelmax_first, &flocopt))
        goto error;

      const size_t bwidth = ROUNDUP(width, flocopt.sizex);
      const size_t bheight = ROUNDUP(height, flocopt.sizey);

      const int bufsize = (bwidth / flocopt.sizex) * (bheight / flocopt.sizey);

      dt_opencl_local_buffer_t slocopt
        = (dt_opencl_local_buffer_t){ .xoffset = 0, .xfactor = 1, .yoffset = 0, .yfactor = 1,
                                      .cellsize = sizeof(float), .overhead = 0,
                                      .sizex = 1 << 16, .sizey = 1 };

      if(!dt_opencl_local_buffer_opt(devid, gd->kernel_pixelmax_second, &slocopt))
        goto error;

      const int reducesize = MIN(REDUCESIZE, ROUNDUP(bufsize, slocopt.sizex) / slocopt.sizex);

      size_t sizes[3];
      size_t local[3];

      dev_m = dt_opencl_alloc_device_buffer(devid, (size_t)bufsize * sizeof(float));
      if(dev_m == NULL) goto error;

      dev_r = dt_opencl_alloc_device_buffer(devid, (size_t)reducesize * sizeof(float));
      if(dev_r == NULL) goto error;

      sizes[0] = bwidth;
      sizes[1] = bheight;
      sizes[2] = 1;
      local[0] = flocopt.sizex;
      local[1] = flocopt.sizey;
      local[2] = 1;
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_first, 0, sizeof(cl_mem), &dev_in);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_first, 1, sizeof(int), &width);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_first, 2, sizeof(int), &height);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_first, 3, sizeof(cl_mem), &dev_m);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_first, 4, flocopt.sizex * flocopt.sizey * sizeof(float), NULL);
      err = dt_opencl_enqueue_kernel_2d_with_local(devid, gd->kernel_pixelmax_first, sizes, local);
      if(err != CL_SUCCESS) goto error;

      sizes[0] = reducesize * slocopt.sizex;
      sizes[1] = 1;
      sizes[2] = 1;
      local[0] = slocopt.sizex;
      local[1] = 1;
      local[2] = 1;
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_second, 0, sizeof(cl_mem), &dev_m);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_second, 1, sizeof(cl_mem), &dev_r);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_second, 2, sizeof(int), &bufsize);
      dt_opencl_set_kernel_arg(devid, gd->kernel_pixelmax_second, 3, slocopt.sizex * sizeof(float), NULL);
      err = dt_opencl_enqueue_kernel_2d_with_local(devid, gd->kernel_pixelmax_second, sizes, local);
      if(err != CL_SUCCESS) goto error;

      maximum = dt_alloc_align(16, reducesize * sizeof(float));
      err = dt_opencl_read_buffer_from_device(devid, (void *)maximum, dev_r, 0,
                                            (size_t)reducesize * sizeof(float), CL_TRUE);
      if(err != CL_SUCCESS) goto error;

      dt_opencl_release_mem_object(dev_r);
      dt_opencl_release_mem_object(dev_m);
      dev_r = dev_m = NULL;

      for(int k = 1; k < reducesize; k++)
      {
        float mine = maximum[0];
        float other = maximum[k];
        maximum[0] = (other > mine) ? other : mine;
      }

      tmp_lwmax = MAX(eps, (maximum[0] * 0.01f));

      dt_free_align(maximum);
      maximum = NULL;
    }

    const float lwmax = tmp_lwmax;
    const float ldc = d->drago.max_light * 0.01f / log10f(lwmax + 1.0f);
    const float bl = logf(MAX(eps, d->drago.bias)) / logf(0.5f);

    parameters[0] = eps;
    parameters[1] = ldc;
    parameters[2] = bl;
    parameters[3] = lwmax;

    if(self->dev->gui_attached && g && piece->pipe->type == DT_DEV_PIXELPIPE_PREVIEW)
    {
      uint64_t hash = dt_dev_hash_plus(self->dev, piece->pipe, 0, self->priority);
      dt_pthread_mutex_lock(&g->lock);
      g->lwmax = lwmax;
      g->hash = hash;
      dt_pthread_mutex_unlock(&g->lock);
    }
  }

  const float scale = piece->iscale / roi_in->scale;
  const float sigma_r = 8.0f; // does not depend on scale
  const float iw = piece->buf_in.width / scale;
  const float ih = piece->buf_in.height / scale;
  const float sigma_s = fminf(iw, ih) * 0.03f;

  if(d->detail != 0.0f)
  {
    b = dt_bilateral_init_cl(devid, roi_in->width, roi_in->height, sigma_s, sigma_r);
    if(!b) goto error;
    // get detail from unchanged input buffer
    err = dt_bilateral_splat_cl(b, dev_in);
    if(err != CL_SUCCESS) goto error;
  }

  size_t sizes[2] = { ROUNDUPWD(width), ROUNDUPHT(height) };
  dt_opencl_set_kernel_arg(devid, gtkernel, 0, sizeof(cl_mem), &dev_in);
  dt_opencl_set_kernel_arg(devid, gtkernel, 1, sizeof(cl_mem), &dev_out);
  dt_opencl_set_kernel_arg(devid, gtkernel, 2, sizeof(int), &width);
  dt_opencl_set_kernel_arg(devid, gtkernel, 3, sizeof(int), &height);
  dt_opencl_set_kernel_arg(devid, gtkernel, 4, 4 * sizeof(float), &parameters);
  err = dt_opencl_enqueue_kernel_2d(devid, gtkernel, sizes);
  if(err != CL_SUCCESS) goto error;

  if(d->detail != 0.0f)
  {
    err = dt_bilateral_blur_cl(b);
    if(err != CL_SUCCESS) goto error;
    // and apply it to output buffer after logscale
    err = dt_bilateral_slice_to_output_cl(b, dev_in, dev_out, d->detail);
    if(err != CL_SUCCESS) goto error;
    dt_bilateral_free_cl(b);
  }

  return TRUE;

error:
  if(b) dt_bilateral_free_cl(b);
  dt_opencl_release_mem_object(dev_m);
  dt_opencl_release_mem_object(dev_r);
  dt_free_align(maximum);
  dt_print(DT_DEBUG_OPENCL, "[opencl_global_tonemap] couldn't enqueue kernel! %d\n", err);
  return FALSE;
}
#endif


void tiling_callback(struct dt_iop_module_t *self, struct dt_dev_pixelpipe_iop_t *piece,
                     const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out,
                     struct dt_develop_tiling_t *tiling)
{
  dt_iop_global_tonemap_data_t *d = (dt_iop_global_tonemap_data_t *)piece->data;

  const float scale = piece->iscale / roi_in->scale;
  const float iw = piece->buf_in.width / scale;
  const float ih = piece->buf_in.height / scale;
  const float sigma_s = fminf(iw, ih) * 0.03f;
  const float sigma_r = 8.0f;
  const int detail = (d->detail != 0.0f);

  const int width = roi_in->width;
  const int height = roi_in->height;
  const int channels = piece->colors;

  const size_t basebuffer = width * height * channels * sizeof(float);

  tiling->factor = 2.0f + (detail ? (float)dt_bilateral_memory_use2(width, height, sigma_s, sigma_r) / basebuffer : 0.0f);
  tiling->maxbuf
      = (detail ? MAX(1.0f, (float)dt_bilateral_singlebuffer_size2(width, height, sigma_s, sigma_r) / basebuffer) : 1.0f);
  tiling->overhead = 0;
  tiling->overlap = (detail ? ceilf(4 * sigma_s) : 0);
  tiling->xalign = 1;
  tiling->yalign = 1;
  return;
}

void commit_params(struct dt_iop_module_t *self, dt_iop_params_t *p1, dt_dev_pixelpipe_t *pipe,
                   dt_dev_pixelpipe_iop_t *piece)
{
  dt_iop_global_tonemap_params_t *p = (dt_iop_global_tonemap_params_t *)p1;
  dt_iop_global_tonemap_data_t *d = (dt_iop_global_tonemap_data_t *)piece->data;

  d->operator= p->operator;
  d->drago.bias = p->drago.bias;
  d->drago.max_light = p->drago.max_light;
  d->detail = p->detail;

  // drago needs the maximum L-value of the whole image so it must not use tiling
  if(d->operator == OPERATOR_DRAGO) piece->process_tiling_ready = 0;

#ifdef HAVE_OPENCL
  if(d->detail != 0.0f)
    piece->process_cl_ready = (piece->process_cl_ready && !(darktable.opencl->avoid_atomics));
#endif
}