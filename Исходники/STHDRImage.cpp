/* Load image data from file in PFM format */
STStatus
STHDRImage::LoadPFM(const char* filename) {
  FILE* fin = fopen(filename, "rb");
  char buffer[128];

  if (fin == NULL) {
    printf("Error opening file: %s\n", filename);
    return ST_ERROR;
  }

  // Check the format
  char format;
  fgets(buffer, 80, fin);
  if ( sscanf(buffer, "P%c", &format) != 1 || (format != 'f' && format != 'F') ) {
    printf("Invalid PFM file\n");
    fclose(fin);
    return ST_ERROR;
  }
  // Get the dimensions
  int w, h;
  fgets(buffer, 80, fin);
  if ( sscanf(buffer, "%i %i", &w, &h) != 2 || w <= 0 || h <= 0 ) {
    printf("Invalid PFM file\n");
    fclose(fin);
    return ST_ERROR;
  }
  // Get the scale factor, we just discard this
  // FIXME endianness
  float scale;
  fgets(buffer, 80, fin);
  if ( sscanf(buffer, "%f", &scale) != 1 ) {
    printf("Invalid PFM file\n");
    fclose(fin);
    return ST_ERROR;
  }

  mWidth = w;
  mHeight = h;
  mPixels = new STHDRImage::Pixel[w*h];

  // Now we can read the data
  if (format == 'f') { // grayscale
    float gval;
    for(int j = 0; j < h; j++) {
      for(int i = 0; i < w; i++) {
        if ( fread(&gval, sizeof(float), 1, fin) != 1 ) {
          printf("Invalid PFM file\n");
          fclose(fin);
          return ST_ERROR;
        }
        SetPixel(i,j, STHDRImage::Pixel(gval, gval, gval));
      }
    }
  }
  else { // if (format == 'F') color
    if ( fread(mPixels, sizeof(STHDRImage::Pixel), w*h, fin) != w*h ) {
      printf("Invalid PFM file\n");
      fclose(fin);
      return ST_ERROR;
    }
  }

  fclose(fin);

  return ST_OK;
}