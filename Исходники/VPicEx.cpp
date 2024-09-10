/* Ramp colors to form a gradient between two specificed colors. 
   For 8-bit images set up to ramp the palette, for 24-bit
   images ramp three lookup tables
*/
int rampcolors(COLORAMP *ramp, imgdes *srcimg, imgdes *resimg)
{
   int rcode, buffsize=256, j;
   static UCHAR *redlut, *grnlut, *blulut;

   copyimage(srcimg, resimg);
   switch(srcimg->bmh->biBitCount){
   case (8):
      resimg->palette[ramp->lo].rgbRed = ramp->lored;
      resimg->palette[ramp->lo].rgbGreen = ramp->logrn;
      resimg->palette[ramp->lo].rgbBlue = ramp->loblu;
      resimg->palette[ramp->hi].rgbRed = ramp->hired;
      resimg->palette[ramp->hi].rgbGreen = ramp->higrn;
      resimg->palette[ramp->hi].rgbBlue  = ramp->hiblu;
      ramppalette(ramp->lo,ramp-> hi, resimg->palette);
      resimg->imgtype = 0;  // Make sure it's not considered grayscale
      rcode = updatebitmapcolortable(resimg);
      break;
   case (24):
      redlut = (UCHAR far*)malloc(buffsize);
      grnlut = (UCHAR far*)malloc(buffsize);
      blulut = (UCHAR far*)malloc(buffsize);
      for(j=0; j<256; j++) {
         redlut[j] = grnlut[j] = blulut[j] = j;
         }
      redlut[ramp->lo] = ramp->lored; 
      grnlut[ramp->lo] = ramp->logrn; 
      blulut[ramp->lo] = ramp->loblu;
      redlut[ramp->hi] = ramp->hired;
      grnlut[ramp->hi] = ramp->higrn;
      blulut[ramp->hi] = ramp->hiblu;

      ramplut(ramp->lo, ramp->hi, redlut);
      ramplut(ramp->lo, ramp->hi, grnlut);
      ramplut(ramp->lo, ramp->hi, blulut);
      rcode = usetable(redlut, grnlut, blulut, resimg, resimg);
      free(blulut);
      free(grnlut);
      free(redlut);
      break;
   case (1):
      rcode = BAD_BPP;
   }
   return(rcode);
}