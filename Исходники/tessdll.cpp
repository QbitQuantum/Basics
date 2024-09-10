int TessDllAPI::BeginPageUpright(uinT32 xsize,uinT32 ysize,unsigned char *buf, uinT8 bpp) {


    EndPage();

//It looks like Adaptive thresholding is disabled so this must be a 1 bpp image
  if (page_image.create (xsize+800, ysize+800, 1)==-1)
    return 0L;  //make the image bigger to enclose in whitespace

  //copy the passed buffer into the center of the image
  IMAGE tmp;

  tmp.capture(buf, xsize, ysize, bpp);


  copy_sub_image(&tmp, 0, 0, 0, 0, &page_image, 400, 400, true);



  return ProcessPagePass1();
}