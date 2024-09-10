void floats_to_bytes_from_file_ext(const char *inFile, const char *outFile,
  char *band, float mask, scale_t scaling, float scale_factor)
{
  FILE *fp;
  meta_parameters *meta;
  float *float_data;
  unsigned char *byte_data;
  int ii, band_number;
  long long pixel_count;
  long offset;

  meta = meta_read(inFile);
  band_number = (!band || strlen(band) == 0 || strcmp(band, "???")==0) ? 0 :
    get_band_number(meta->general->bands, meta->general->band_count, band);
  pixel_count = meta->general->line_count * meta->general->sample_count;
  offset = meta->general->line_count * band_number;
  float_data = (float *) MALLOC(sizeof(float) * pixel_count);
  fp = FOPEN(inFile, "rb");
  get_float_lines(fp, meta, offset, meta->general->line_count, float_data);
  FCLOSE(fp);
  byte_data = floats_to_bytes_ext(float_data, pixel_count, mask, scaling,
    scale_factor);
  for (ii=0; ii<pixel_count; ii++)
    float_data[ii] = (float) byte_data[ii];
  meta->general->data_type = ASF_BYTE;
  meta_write(meta, outFile);
  fp = FOPEN(outFile, "wb");
  put_float_lines(fp, meta, offset, meta->general->line_count, float_data);
  FCLOSE(fp);
  FREE(float_data);
  FREE(byte_data);
  meta_free(meta);
}