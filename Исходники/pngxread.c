int PNGAPI
pngx_read_image(png_structp png_ptr, png_infop info_ptr,
                png_charp fmt_name_buf, png_size_t fmt_name_buf_size,
                png_charp fmt_desc_buf, png_size_t fmt_desc_buf_size)
{
   png_byte sig[128];
   png_size_t num;
   int (*read_fn)(png_structp, png_infop, FILE *);
   FILE *stream;
   fpos_t fpos;
   int result;

   /* Precondition. */
#ifdef PNG_FLAG_MALLOC_NULL_MEM_OK
   PNGX_ASSERT_MSG(!(png_ptr->flags & PNG_FLAG_MALLOC_NULL_MEM_OK),
      "pngxtern requires a safe allocator");
#endif

   /* Check the format name buffers. */
   /* Ensure that the longest short name ("PNG datastream") and
    * the longest long name ("Portable Network Graphics embedded datastream")
    * will fit.
    */
   if ((fmt_name_buf != NULL &&
        fmt_name_buf_size < sizeof(pngx_png_datastream_fmt_name)) ||
       (fmt_desc_buf != NULL &&
        fmt_desc_buf_size < sizeof(pngx_png_datastream_fmt_desc)))
      return -1;  /* invalid parameters */

   /* Read the signature bytes. */
   stream = (FILE *)png_get_io_ptr(png_ptr);
   PNGX_ASSERT(stream != NULL);
   if (fgetpos(stream, &fpos) != 0)
      png_error(png_ptr, "Can't ftell in input file stream");
   num = fread(sig, 1, sizeof(sig), stream);
   if (fsetpos(stream, &fpos) != 0)
      png_error(png_ptr, "Can't fseek in input file stream");

   /* Try the PNG format first. */
   if (pngx_sig_is_png(png_ptr, sig, num,
       fmt_name_buf, fmt_name_buf_size, fmt_desc_buf, fmt_desc_buf_size) > 0)
   {
      png_read_png(png_ptr, info_ptr, 0, NULL);
      if (getc(stream) != EOF)
      {
         png_warning(png_ptr, "Extraneous data found after IEND");
         fseek(stream, 0, SEEK_END);
      }
      return 1;
   }

   /* Check the signature bytes against other known image formats. */
   if (pngx_sig_is_bmp(sig, num,
       fmt_name_buf, fmt_name_buf_size, fmt_desc_buf, fmt_desc_buf_size) > 0)
      read_fn = pngx_read_bmp;
   else if (pngx_sig_is_gif(sig, num,
       fmt_name_buf, fmt_name_buf_size, fmt_desc_buf, fmt_desc_buf_size) > 0)
      read_fn = pngx_read_gif;
   else if (pngx_sig_is_jpeg(sig, num,
       fmt_name_buf, fmt_name_buf_size, fmt_desc_buf, fmt_desc_buf_size) > 0)
      read_fn = pngx_read_jpeg;
   else if (pngx_sig_is_pnm(sig, num,
       fmt_name_buf, fmt_name_buf_size, fmt_desc_buf, fmt_desc_buf_size) > 0)
      read_fn = pngx_read_pnm;
   else if (pngx_sig_is_tiff(sig, num,
       fmt_name_buf, fmt_name_buf_size, fmt_desc_buf, fmt_desc_buf_size) > 0)
      read_fn = pngx_read_tiff;
   else
      return 0;  /* not a known image format */

   /* Read the image. */
   result = read_fn(png_ptr, info_ptr, stream);
   /* Signature checking may give false positives; reading can still fail. */
   if (result <= 0)  /* this isn't the format we thought it was */
      if (fsetpos(stream, &fpos) != 0)
         png_error(png_ptr, "Can't fseek in input file stream");
   return result;
}