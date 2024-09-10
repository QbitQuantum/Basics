void R_LoadJPG(const char *filename, unsigned char **pic, int *width, int *height)
{
  /* This struct contains the JPEG decompression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   */
  struct jpeg_decompress_struct cinfo = {NULL};
  /* We use our private extension JPEG error handler.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  /* This struct represents a JPEG error handler.  It is declared separately
   * because applications often want to supply a specialized error handler
   * (see the second half of this file for an example).  But here we just
   * take the easy way out and use the standard error handler, which will
   * print a message on stderr and call exit() if compression fails.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct jpeg_error_mgr jerr;
  /* More stuff */
  JSAMPARRAY buffer;		/* Output row buffer */
  unsigned int row_stride;	/* physical row width in output buffer */
  unsigned int pixelcount, memcount;
  unsigned int sindex, dindex;
  byte *out;
  int len;
	union {
		byte *b;
		void *v;
	} fbuffer;
  byte  *buf;

  /* In this example we want to open the input file before doing anything else,
   * so that the setjmp() error recovery below can assume the file is open.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to read binary files.
   */

  len = ri.FS_ReadFile ( ( char * ) filename, &fbuffer.v);
  if (!fbuffer.b || len < 0) {
	return;
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo.err = jpeg_std_error(&jerr);
  cinfo.err->error_exit = R_JPGErrorExit;
  cinfo.err->output_message = R_JPGOutputMessage;

  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_mem_src(&cinfo, fbuffer.b, len);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void) jpeg_read_header(&cinfo, TRUE);
  /* We can ignore the return value from jpeg_read_header since
   *   (a) suspension is not possible with the stdio data source, and
   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
   * See libjpeg.doc for more info.
   */

  /* Step 4: set parameters for decompression */

  /*
   * Make sure it always converts images to RGB color space. This will
   * automatically convert 8-bit greyscale images to RGB as well.
   */
  cinfo.out_color_space = JCS_RGB;

  /* Step 5: Start decompressor */

  (void) jpeg_start_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* We may need to do some setup of our own at this point before reading
   * the data.  After jpeg_start_decompress() we have the correct scaled
   * output image dimensions available, as well as the output colormap
   * if we asked for color quantization.
   * In this example, we need to make an output work buffer of the right size.
   */ 
  /* JSAMPLEs per row in output buffer */

  pixelcount = cinfo.output_width * cinfo.output_height;

  if(!cinfo.output_width || !cinfo.output_height
      || ((pixelcount * 4) / cinfo.output_width) / 4 != cinfo.output_height
      || pixelcount > 0x1FFFFFFF || cinfo.output_components != 3
    )
  {
    // Free the memory to make sure we don't leak memory
    ri.FS_FreeFile (fbuffer.v);
    jpeg_destroy_decompress(&cinfo);
  
    ri.Error(ERR_DROP, "LoadJPG: %s has an invalid image format: %dx%d*4=%d, components: %d", filename,
		    cinfo.output_width, cinfo.output_height, pixelcount * 4, cinfo.output_components);
  }

  memcount = pixelcount * 4;
  row_stride = cinfo.output_width * cinfo.output_components;

  out = ri.Malloc(memcount);

  *width = cinfo.output_width;
  *height = cinfo.output_height;

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo.output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */
  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
	buf = ((out+(row_stride*cinfo.output_scanline)));
	buffer = &buf;
    (void) jpeg_read_scanlines(&cinfo, buffer, 1);
  }
  
  buf = out;

  // Expand from RGB to RGBA
  sindex = pixelcount * cinfo.output_components;
  dindex = memcount;

  do
  {	
    buf[--dindex] = 255;
    buf[--dindex] = buf[--sindex];
    buf[--dindex] = buf[--sindex];
    buf[--dindex] = buf[--sindex];
  } while(sindex);

  *pic = out;

  /* Step 7: Finish decompression */

  jpeg_finish_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  /* After finish_decompress, we can close the input file.
   * Here we postpone it until after no more JPEG errors are possible,
   * so as to simplify the setjmp error logic above.  (Actually, I don't
   * think that jpeg_destroy can do an error exit, but why assume anything...)
   */
  ri.FS_FreeFile (fbuffer.v);

  /* At this point you may want to check to see whether any corrupt-data
   * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
   */

  /* And we're done! */
}