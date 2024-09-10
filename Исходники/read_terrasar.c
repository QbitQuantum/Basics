int read_terrasar_client(int row_start, int n_rows_to_get,
			 void *dest_void, void *read_client_info,
			 meta_parameters *meta, int data_type)
{
  ReadTerrasarClientInfo *info = (ReadTerrasarClientInfo*) read_client_info;
  float *dest = (float*)dest_void;
  int ii, jj, ns = meta->general->sample_count;
  int skip = 1;
  if (info->multilook) {
    skip = meta->sar->look_count;
    row_start *= skip;
  }
  // Read in the image
  short int *shorts = MALLOC(sizeof(short int)*ns*2);
  for (ii=0; ii<n_rows_to_get; ii++) {
    long long offset = 
      (long long) (info->header + (ii*skip + row_start) * info->width);
    FSEEK(info->fp, offset, SEEK_SET);
    FREAD(shorts, sizeof(short int), ns*2, info->fp);
    for (jj=0; jj<ns; jj++) 
      dest[jj + ii*ns] = hypot(shorts[jj*2], shorts[jj*2+1]);
  }
  free(shorts);

  return TRUE;
}