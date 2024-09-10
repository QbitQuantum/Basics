LICE_IBitmap *LICE_LoadJPGFromResource(HINSTANCE hInst, const char *resid, LICE_IBitmap *bmp)
{
#ifdef _WIN32
  HRSRC hResource = FindResource(hInst, resid, "JPG");
  if(!hResource) return NULL;

  DWORD imageSize = SizeofResource(hInst, hResource);
  if(imageSize < 8) return NULL;

  HGLOBAL res = LoadResource(hInst, hResource);
  const void* pResourceData = LockResource(res);
  if(!pResourceData) return NULL;

  unsigned char *data = (unsigned char *)pResourceData;

  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr={0,};
  JSAMPARRAY buffer;
  int row_stride;

  jerr.pub.error_exit = LICEJPEG_Error;
  jerr.pub.emit_message = LICEJPEG_EmitMsg;
  jerr.pub.output_message = LICEJPEG_OutMsg;
  jerr.pub.format_message = LICEJPEG_FmtMsg;
  jerr.pub.reset_error_mgr = LICEJPEG_reset_error_mgr;

  cinfo.err = &jerr.pub;

  if (setjmp(jerr.setjmp_buffer)) 
  {
    jpeg_destroy_decompress(&cinfo);
    return 0;
  }
  jpeg_create_decompress(&cinfo);

  cinfo.src = (struct jpeg_source_mgr *) (*cinfo.mem->alloc_small) ((j_common_ptr) &cinfo, JPOOL_PERMANENT, sizeof (struct jpeg_source_mgr));
  
  cinfo.src->init_source = LICEJPEG_init_source;
  cinfo.src->fill_input_buffer = LICEJPEG_fill_input_buffer;
  cinfo.src->skip_input_data = LICEJPEG_skip_input_data;
  cinfo.src->resync_to_restart = jpeg_resync_to_restart;	
  cinfo.src->term_source = LICEJPEG_term_source;

  cinfo.src->next_input_byte = data;
  cinfo.src->bytes_in_buffer = imageSize;

  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;

  buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

  LICE_IBitmap *delbmp = NULL;
  if (bmp) bmp->resize(cinfo.output_width,cinfo.output_height);
  else delbmp = bmp = new WDL_NEW LICE_MemBitmap(cinfo.output_width,cinfo.output_height);

  if (!bmp || bmp->getWidth() != (int)cinfo.output_width || bmp->getHeight() != (int)cinfo.output_height) 
  {
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    delete delbmp;
    return 0;
  }

  LICE_pixel *bmpptr = bmp->getBits();
  int dbmpptr=bmp->getRowSpan();
  if (bmp->isFlipped())
  {
    bmpptr += dbmpptr*(bmp->getHeight()-1);
    dbmpptr=-dbmpptr;
  }

  while (cinfo.output_scanline < cinfo.output_height)
  {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    jpeg_read_scanlines(&cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
//    put_scanline_someplace(buffer[0], row_stride);
    if (cinfo.output_components==3)
    {
      int x;
      for (x = 0; x < (int)cinfo.output_width; x++)
      {
        bmpptr[x]=LICE_RGBA(buffer[0][x*3],buffer[0][x*3+1],buffer[0][x*3+2],255);
      }
    }
    else if (cinfo.output_components==1)
    {
      int x;
      for (x = 0; x < (int)cinfo.output_width; x++)
      {
        int v=buffer[0][x];
        bmpptr[x]=LICE_RGBA(v,v,v,255);
      }
    }
    else
    {
      memset(bmpptr,0,4*cinfo.output_width);
    }
    bmpptr+=dbmpptr;
  }

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);  // we created cinfo.src with some special alloc so I think it gets collected

  return bmp;

#else
  return 0;
#endif
}