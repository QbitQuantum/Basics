int
process_cl (struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, cl_mem dev_in, cl_mem dev_out, const dt_iop_roi_t *roi_in, const dt_iop_roi_t *roi_out)
{
  dt_iop_soften_data_t *d = (dt_iop_soften_data_t *)piece->data;
  dt_iop_soften_global_data_t *gd = (dt_iop_soften_global_data_t *)self->data;

  cl_int err = -999;
  cl_mem dev_m = NULL;
  const int devid = piece->pipe->devid;
  const int width = roi_in->width;
  const int height = roi_in->height;

  const float brightness = 1.0f / exp2f ( -d->brightness );
  const float saturation = d->saturation/100.0f;
  const float amount = d->amount/100.0f;

  const float w = piece->iwidth*piece->iscale;
  const float h = piece->iheight*piece->iscale;
  int mrad = sqrt( w*w + h*h) * 0.01f;

  int rad = mrad*(fmin(100.0f, d->size+1)/100.0f);
  const int radius = MIN(mrad, ceilf(rad * roi_in->scale / piece->iscale));

  /* sigma-radius correlation to match opencl vs. non-opencl. identified by numerical experiments but unproven. ask me if you need details. ulrich */
  const float sigma = sqrt((radius * (radius + 1) * BOX_ITERATIONS + 2)/3.0f);
  const int wdh = ceilf(3.0f * sigma);
  const int wd = 2 * wdh + 1;
  float mat[wd];
  float *m = mat + wdh;
  float weight = 0.0f;

  // init gaussian kernel
  for(int l=-wdh; l<=wdh; l++) weight += m[l] = expf(- (l*l)/(2.f*sigma*sigma));
  for(int l=-wdh; l<=wdh; l++) m[l] /= weight;

  // for(int l=-wdh; l<=wdh; l++) printf("%.6f ", (double)m[l]);
  // printf("\n");


  size_t maxsizes[3] = { 0 };        // the maximum dimensions for a work group
  size_t workgroupsize = 0;          // the maximum number of items in a work group
  unsigned long localmemsize = 0;    // the maximum amount of local memory we can use
  size_t kernelworkgroupsize = 0;    // the maximum amount of items in work group for this kernel
  
  // make sure blocksize is not too large
  int blocksize = BLOCKSIZE;
  if(dt_opencl_get_work_group_limits(devid, maxsizes, &workgroupsize, &localmemsize) == CL_SUCCESS &&
     dt_opencl_get_kernel_work_group_size(devid, gd->kernel_soften_hblur, &kernelworkgroupsize) == CL_SUCCESS)
  {
    // reduce blocksize step by step until it fits to limits
    while(blocksize > maxsizes[0] || blocksize > maxsizes[1] || blocksize > kernelworkgroupsize
          || blocksize > workgroupsize || (blocksize+2*wdh)*4*sizeof(float) > localmemsize)
    {
      if(blocksize == 1) break;
      blocksize >>= 1;    
    }
  }
  else
  {