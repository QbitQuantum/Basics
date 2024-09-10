/**
 * Dump an image to a .raw or .ppm file (depends on OS).
 * \param format  PIPE_FORMAT_x
 * \param cpp  bytes per pixel
 * \param width  width in pixels
 * \param height height in pixels
 * \param stride  row stride in bytes
 */
void debug_dump_image(const char *prefix,
                      unsigned format, unsigned cpp,
                      unsigned width, unsigned height,
                      unsigned stride,
                      const void *data)     
{
#ifdef PIPE_SUBSYSTEM_WINDOWS_DISPLAY
   static unsigned no = 0; 
   char filename[256];
   WCHAR wfilename[sizeof(filename)];
   ULONG_PTR iFile = 0;
   struct {
      unsigned format;
      unsigned cpp;
      unsigned width;
      unsigned height;
   } header;
   unsigned char *pMap = NULL;
   unsigned i;

   util_snprintf(filename, sizeof(filename), "\\??\\c:\\%03u%s.raw", ++no, prefix);
   for(i = 0; i < sizeof(filename); ++i)
      wfilename[i] = (WCHAR)filename[i];
   
   pMap = (unsigned char *)EngMapFile(wfilename, sizeof(header) + height*width*cpp, &iFile);
   if(!pMap)
      return;
   
   header.format = format;
   header.cpp = cpp;
   header.width = width;
   header.height = height;
   memcpy(pMap, &header, sizeof(header));
   pMap += sizeof(header);
   
   for(i = 0; i < height; ++i) {
      memcpy(pMap, (unsigned char *)data + stride*i, cpp*width);
      pMap += cpp*width;
   }
      
   EngUnmapFile(iFile);
#elif defined(PIPE_OS_UNIX)
   /* write a ppm file */
   char filename[256];
   FILE *f;

   util_snprintf(filename, sizeof(filename), "%s.ppm", prefix);

   f = fopen(filename, "w");
   if (f) {
      int i, x, y;
      int r, g, b;
      const uint8_t *ptr = (uint8_t *) data;

      /* XXX this is a hack */
      switch (format) {
      case PIPE_FORMAT_B8G8R8A8_UNORM:
         r = 2;
         g = 1;
         b = 0;
         break;
      default:
         r = 0;
         g = 1;
         b = 1;
      }

      fprintf(f, "P6\n");
      fprintf(f, "# ppm-file created by osdemo.c\n");
      fprintf(f, "%i %i\n", width, height);
      fprintf(f, "255\n");
      fclose(f);

      f = fopen(filename, "ab");  /* reopen in binary append mode */
      for (y = 0; y < height; y++) {
         for (x = 0; x < width; x++) {
            i = y * stride + x * cpp;
            fputc(ptr[i + r], f); /* write red */
            fputc(ptr[i + g], f); /* write green */
            fputc(ptr[i + b], f); /* write blue */
         }
      }
      fclose(f);
   }
   else {
      fprintf(stderr, "Can't open %s for writing\n", filename);
   }
#endif
}