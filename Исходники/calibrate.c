int asf_logscale(const char *inFile, const char *outFile)
{
  int ii, jj, kk;
  meta_parameters *meta = meta_read(inFile);
  int band_count = meta->general->band_count;
  int sample_count = meta->general->sample_count;
  int line_count = meta->general->line_count;
  float *bufIn = (float *) MALLOC(sizeof(float)*sample_count);
  float *bufOut = (float *) MALLOC(sizeof(float)*sample_count);
  
  char *input = appendExt(inFile, ".img");
  char *output = appendExt(outFile, ".img");
  FILE *fpIn = FOPEN(input, "rb");
  FILE *fpOut = FOPEN(output, "wb");
  for (kk=0; kk<band_count; kk++) {
    for (ii=0; ii<line_count; ii++) {
      get_band_float_line(fpIn, meta, kk, ii, bufIn);
      for (jj=0; jj<sample_count; jj++) {
	if (FLOAT_EQUIVALENT(bufIn[jj], 0.0))
	  bufOut[jj] = 0.0;
	else
	  bufOut[jj] = 10.0 * log10(bufIn[jj]);
      }
      put_band_float_line(fpOut, meta, kk, ii, bufOut);
      asfLineMeter(ii, line_count);
    }
  }
  meta_write(meta, outFile);
  meta_free(meta);
  FCLOSE(fpIn);
  FCLOSE(fpOut);
  FREE(bufIn);
  FREE(bufOut);
  FREE(input);
  FREE(output);

  return FALSE;
}