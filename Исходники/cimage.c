CImage *Convert2CImage(Image *img)
{
  CImage *imgc;
  int i;

  imgc = (CImage *) calloc(1,sizeof(CImage));
  if (imgc == NULL){
    Error(MSG1,"CopyCImage");
  }
  for (i=0; i<3; i++)
    imgc->C[i] = CopyImage(img);
  return imgc;
}