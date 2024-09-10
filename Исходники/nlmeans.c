int
process_cl (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, cl_mem dev_in, cl_mem dev_out, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  dt_iop_nlmeans_params_t *d = (dt_iop_nlmeans_params_t *)piece->data;
  dt_iop_nlmeans_global_data_t *gd = (dt_iop_nlmeans_global_data_t *)self->data;


  const int devid = piece->pipe->devid;
  const int width = roi_in->width;
  const int height = roi_in->height;

  cl_mem dev_U4 = NULL;
  cl_mem dev_U4_t = NULL;

  cl_int err = -999;

  const int P = ceilf(d->radius * roi_in->scale / piece->iscale); // pixel filter size
  const int K = ceilf(7 * roi_in->scale / piece->iscale); // nbhood
  const float sharpness = 3000.0f/(1.0f+d->strength);

  if(P < 1)
  {
    size_t origin[] = { 0, 0, 0};
    size_t region[] = { width, height, 1};
    err = dt_opencl_enqueue_copy_image(devid, dev_in, dev_out, origin, origin, region);
    if (err != CL_SUCCESS) goto error;
    return TRUE;
  }

  float max_L = 120.0f, max_C = 512.0f;
  float nL = 1.0f/max_L, nC = 1.0f/max_C;
  float nL2 = nL*nL, nC2 = nC*nC;
  //float weight[4] = { powf(d->luma, 0.6), powf(d->chroma, 0.6), powf(d->chroma, 0.6), 1.0f };
  float weight[4] = { d->luma, d->chroma, d->chroma, 1.0f };

  dev_U4 = dt_opencl_alloc_device(devid, roi_out->width, roi_out->height, sizeof(float));
  if (dev_U4 == NULL) goto error;

  dev_U4_t = dt_opencl_alloc_device(devid, roi_out->width, roi_out->height, sizeof(float));
  if (dev_U4_t == NULL) goto error;


  // prepare local work group
  size_t maxsizes[3] = { 0 };        // the maximum dimensions for a work group
  size_t workgroupsize = 0;          // the maximum number of items in a work group
  unsigned long localmemsize = 0;    // the maximum amount of local memory we can use
  size_t kernelworkgroupsize = 0;    // the maximum amount of items in work group of the kernel
  // assuming this is the same for nlmeans_horiz and nlmeans_vert

  // make sure blocksize is not too large
  int blocksize = BLOCKSIZE;
  if(dt_opencl_get_work_group_limits(devid, maxsizes, &workgroupsize, &localmemsize) == CL_SUCCESS &&
      dt_opencl_get_kernel_work_group_size(devid, gd->kernel_nlmeans_horiz, &kernelworkgroupsize) == CL_SUCCESS)
  {
    // reduce blocksize step by step until it fits to limits
    while(blocksize > maxsizes[0] || blocksize > maxsizes[1] || blocksize > kernelworkgroupsize
          || blocksize > workgroupsize || (blocksize+2*P)*sizeof(float) > localmemsize)
    {
      if(blocksize == 1) break;
      blocksize >>= 1;
    }
  }
  else
  {