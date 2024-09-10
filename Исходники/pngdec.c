static void PNGAPI error_function(png_structp png, png_const_charp error) {
  if (error != NULL) fprintf(stderr, "libpng error: %s\n", error);
  longjmp(png_jmpbuf(png), 1);
}