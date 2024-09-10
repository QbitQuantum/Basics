int save_pgm_uint16(const char* path, const uint16_t* image, size_t w, size_t stride, size_t h)
{
  FILE* f = fopen(path, "wb");
  if (f == NULL)
  {
    perror("open");
    return -1;
  }
  fprintf(f, "P5\n");
  fprintf(f, "%lu %lu\n", w, h);
  fprintf(f, "65535\n");
  uint16_t* tmp;
#if __BYTE_ORDER == __LITTLE_ENDIAN
  tmp = (uint16_t*)malloc(w*2);
#endif
  for( size_t y = 0; y < h; ++y)
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    swab(image+stride*y, tmp, w*2);
#else
    tmp = image+stride*y;
#endif
    fwrite(tmp, w*2, 1, f);
  }
#if __BYTE_ORDER == __LITTLE_ENDIAN
  free(tmp);
#endif
  fclose(f);

  return 0;
}