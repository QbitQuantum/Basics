LICE_IBitmap *LICE_LoadPNG(const char *filename, LICE_IBitmap *bmp)
{
  FILE *fp = NULL;
#if defined(_WIN32) && !defined(WDL_NO_SUPPORT_UTF8)
  #ifdef WDL_SUPPORT_WIN9X
  if (GetVersion()<0x80000000)
  #endif
  {
    WCHAR wf[2048];
    if (MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,filename,-1,wf,2048))
      fp = _wfopen(wf,L"rb");
  }
#endif

  if (!fp) fp = fopen(filename,"rb");
  if (!fp) return 0;

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 
  if(!png_ptr) 
  {
    fclose(fp);
    return 0;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr); 
  if(!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, NULL, NULL); 
    fclose(fp);
    return 0;
  }
  
  if (setjmp(png_jmpbuf(png_ptr)))
  { 
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL); 
    fclose(fp);
    return 0;
  }

  png_init_io(png_ptr, fp); 

  png_read_info(png_ptr, info_ptr);

  unsigned int width, height;
  int bit_depth, color_type, interlace_type, compression_type, filter_method;
  png_get_IHDR(png_ptr, info_ptr, &width, &height,
       &bit_depth, &color_type, &interlace_type,
       &compression_type, &filter_method);

  //convert whatever it is to RGBA
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);

  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) 
    png_set_expand_gray_1_2_4_to_8(png_ptr);

  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) 
  {
    png_set_tRNS_to_alpha(png_ptr);
    color_type |= PNG_COLOR_MASK_ALPHA;
  }

  if (bit_depth == 16)
    png_set_strip_16(png_ptr);

  if (bit_depth < 8)
    png_set_packing(png_ptr);

  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);

  if (color_type & PNG_COLOR_MASK_ALPHA)
    png_set_swap_alpha(png_ptr);
  else
    png_set_filler(png_ptr, 0xff, PNG_FILLER_BEFORE);

  LICE_IBitmap *delbmp = NULL;

  if (bmp) bmp->resize(width,height);
  else delbmp = bmp = new WDL_NEW LICE_MemBitmap(width,height);

  if (!bmp || bmp->getWidth() != (int)width || bmp->getHeight() != (int)height) 
  {
    delete delbmp;
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(fp);
    return 0;
  }

  unsigned char **row_pointers=(unsigned char **)malloc(height*sizeof(unsigned char *));;
  LICE_pixel *srcptr = bmp->getBits();
  int dsrcptr=bmp->getRowSpan();
  if (bmp->isFlipped())
  {
    srcptr += dsrcptr*(bmp->getHeight()-1);
    dsrcptr=-dsrcptr;
  }
  unsigned int i;
  for(i=0;i<height;i++)
  {
    row_pointers[i]=(unsigned char *)srcptr;
    srcptr+=dsrcptr;
  }
  png_read_image(png_ptr, row_pointers);
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  fclose(fp);

  #if !(LICE_PIXEL_A == 0 && LICE_PIXEL_R == 1 && LICE_PIXEL_G == 2 && LICE_PIXEL_B == 3)
  for(i=0;i<height;i++)
  {
    unsigned char *bp = row_pointers[i];
    int j=width;
    while (j-->0)
    {
      unsigned char a = bp[0];
      unsigned char r = bp[1];
      unsigned char g = bp[2];
      unsigned char b = bp[3];
      ((LICE_pixel*)bp)[0] = LICE_RGBA(r,g,b,a);
      bp+=4;
    }
  }
  #endif
  free(row_pointers);
  
  return bmp;
}