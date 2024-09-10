void process(struct dt_iop_module_t *self, dt_dev_pixelpipe_iop_t *piece, const void *const ivoid,
             void *const ovoid, const dt_iop_roi_t *const roi_in, const dt_iop_roi_t *const roi_out)
{
  // FIXME: this returns nan!!
  dt_iop_colortransfer_data_t *data = (dt_iop_colortransfer_data_t *)piece->data;
  float *in = (float *)ivoid;
  float *out = (float *)ovoid;
  const int ch = piece->colors;

  if(data->flag == ACQUIRE)
  {
    if(piece->pipe->type == DT_DEV_PIXELPIPE_PREVIEW)
    {
      // only get stuff from the preview pipe, rest stays untouched.
      int hist[HISTN];
      // get histogram of L
      capture_histogram(in, roi_in, hist);
      // invert histogram of L
      invert_histogram(hist, data->hist);

      // get n clusters
      kmeans(in, roi_in, data->n, data->mean, data->var);

      // notify gui that commit_params should let stuff flow back!
      data->flag = ACQUIRED;
      dt_iop_colortransfer_params_t *p = (dt_iop_colortransfer_params_t *)self->params;
      p->flag = ACQUIRE2;
    }
    memcpy(out, in, (size_t)sizeof(float) * ch * roi_out->width * roi_out->height);
  }
  else if(data->flag == APPLY)
  {
    // apply histogram of L and clustering of (a,b)
    int hist[HISTN];
    capture_histogram(in, roi_in, hist);
#ifdef _OPENMP
#pragma omp parallel for default(none) schedule(static) shared(data, in, out, hist)
#endif
    for(int k = 0; k < roi_out->height; k++)
    {
      size_t j = (size_t)ch * roi_out->width * k;
      for(int i = 0; i < roi_out->width; i++)
      {
        // L: match histogram
        out[j] = data->hist[hist[(int)CLAMP(HISTN * in[j] / 100.0, 0, HISTN - 1)]];
        out[j] = CLAMP(out[j], 0, 100);
        j += ch;
      }
    }

    // cluster input buffer
    float(*const mean)[2] = malloc(2 * data->n * sizeof(float));
    float(*const var)[2] = malloc(2 * data->n * sizeof(float));

    kmeans(in, roi_in, data->n, mean, var);

    // get mapping from input clusters to target clusters
    int *const mapio = malloc(data->n * sizeof(int));

    get_cluster_mapping(data->n, mean, data->mean, mapio);

// for all pixels: find input cluster, transfer to mapped target cluster
#ifdef _OPENMP
#pragma omp parallel for default(none) schedule(static) shared(data, in, out)
#endif
    for(int k = 0; k < roi_out->height; k++)
    {
      float weight[MAXN];
      size_t j = (size_t)ch * roi_out->width * k;
      for(int i = 0; i < roi_out->width; i++)
      {
        const float L = in[j];
        const float Lab[3] = { L, in[j + 1], in[j + 2] };
// a, b: subtract mean, scale nvar/var, add nmean
#if 0 // single cluster, gives color banding
        const int ki = get_cluster(in + j, data->n, mean);
        out[j+1] = 100.0/out[j] * ((Lab[1] - mean[ki][0])*data->var[mapio[ki]][0]/var[ki][0] + data->mean[mapio[ki]][0]);
        out[j+2] = 100.0/out[j] * ((Lab[2] - mean[ki][1])*data->var[mapio[ki]][1]/var[ki][1] + data->mean[mapio[ki]][1]);
#else // fuzzy weighting
        get_clusters(in + j, data->n, mean, weight);
        out[j + 1] = out[j + 2] = 0.0f;
        for(int c = 0; c < data->n; c++)
        {
          out[j + 1] += weight[c] * ((Lab[1] - mean[c][0]) * data->var[mapio[c]][0] / var[c][0]
                                     + data->mean[mapio[c]][0]);
          out[j + 2] += weight[c] * ((Lab[2] - mean[c][1]) * data->var[mapio[c]][1] / var[c][1]
                                     + data->mean[mapio[c]][1]);
        }
#endif
        out[j + 3] = in[j + 3];
        j += ch;
      }
    }

    free(mapio);
    free(var);
    free(mean);
  }
  else
  {
    memcpy(out, in, (size_t)sizeof(float) * ch * roi_out->width * roi_out->height);
  }
}