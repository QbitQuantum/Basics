void   seg7_img_draw  (struct seg7_img_t *img, int value)
{
  int i,j;
  int pixel;
 
  pixel = (img->x + img->y*machine.ui.width)*machine.ui.bpp;
  for(i=0; i < img->h; i++)
    {
      int pii = pixel;
      for(j=0; j < img->w; j++)
	{
	  if ((value & img->img[j][i]) != 0)
	    {
	      setpixel(pii,0xee,0x00,0x00); /* on */
	    }
	  else if (img->img[j][i] > 0)
	    {
	      setpixel(pii,0x30,0x30,0x30); /* off */
	    }
	  else
	    {
	      setpixel(pii,0x00,0x00,0x00); /* bkg */
	    }
	  pii += 3;
	}
      pixel += machine.ui.width * machine.ui.bpp;
    }
}