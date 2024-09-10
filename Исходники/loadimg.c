/* *** Die Laderoutine *** */
int LoadImg(char *Filename, MFDB *raster)
{
 IMGHEAD *img;
 long Length;
 int fhndl;

 fhndl=Fopen(Filename, 0);
 if(fhndl<0) return(fhndl);
 Length=Fseek(0L, fhndl, 2);
 Fseek(0L, fhndl, 0);
 img=(void *)Mxalloc(Length, 0);
 if( ((signed long)img)==-32L )  img=(void *)Malloc(Length);
 if( (signed long)img<=0L) { Fclose(fhndl); return((int)img); }
 Fread(fhndl, Length, img);		/* IMG einlesen */
 Fclose(fhndl);

 raster->fd_w = img->LineWidth;
 raster->fd_h = img->Lines;
 raster->fd_wdwidth = (raster->fd_w + 15) / 16;
 raster->fd_stand = 1;
 raster->fd_nplanes = img->Planes;

 Length=(long)raster->fd_wdwidth * 2L * raster->fd_h * raster->fd_nplanes;
 raster->fd_addr=(void *)Mxalloc(Length, 0);
 if( ((signed long)raster->fd_addr)==-32L )
   raster->fd_addr=(void *)Malloc(Length);
 if( (signed long)raster->fd_addr<=0L )  return((int)raster->fd_addr);

 Decompress(img, raster->fd_addr);

 Mfree(img);
 return(0);
}