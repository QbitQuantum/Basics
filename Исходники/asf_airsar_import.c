static void ingest_polarimetry_data(char *inFile, char *inBaseName, 
				    char *outFile, char band, int create)
{
  FILE *fpIn, *fpOut;
  meta_parameters *meta = NULL;
  char tmp[10];
  int ii, kk;
  float *power = NULL;
  char *byteBuf = NULL;
  
  fpIn = FOPEN(inFile, "rb");
  append_ext_if_needed(outFile, ".img", NULL);
  if (create)
    fpOut = FOPEN(outFile, "wb");
  else
    fpOut = FOPEN(outFile, "ab");
  
  if (create) {
    meta = import_airsar_meta(inFile, inBaseName, TRUE);
    meta->general->data_type = REAL32;
    meta->general->band_count = 1;
    sprintf(meta->general->bands, "AMP-%c", band);
    meta->general->image_data_type = IMAGE_LAYER_STACK;
  }
  else {
    meta = meta_read(outFile);
    meta->general->band_count += 1;
    sprintf(tmp, ",AMP-%c", band);
    strcat(meta->general->bands, tmp);
  }      

  power = (float *) MALLOC(sizeof(float)*meta->general->sample_count);
  byteBuf = (char *) MALLOC(sizeof(char)*10);
  airsar_header *header = read_airsar_header(inFile);
  long offset = header->first_data_offset;
  FSEEK(fpIn, offset, SEEK_SET);
  for (ii=0; ii<meta->general->line_count; ii++) {
    for (kk=0; kk<meta->general->sample_count; kk++) {
      FREAD(byteBuf, sizeof(char), 10, fpIn);
      power[kk] = sqrt(((float)byteBuf[1]/254.0 + 1.5) * pow(2, byteBuf[0]));
    }
    put_float_line(fpOut, meta, ii, power);
    asfLineMeter(ii, meta->general->line_count);
  }
  FCLOSE(fpIn);
  FCLOSE(fpOut);
  meta_write(meta, outFile);
  if (power)
    FREE(power);
  if (byteBuf)
    FREE(byteBuf);
  if (meta)
    meta_free(meta);
}