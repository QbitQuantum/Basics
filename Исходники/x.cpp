int main(int argc, char* argv[])
{
  int width = 161, height = 161, layer = 80;
  int i, j;

  nifti_image *nim = NULL;
  char *fin = "/Users/jia/Desktop/F1_58-ed.nii";

  nim = nifti_image_read(fin, 1);
  if (!nim) {
    fprintf(stderr,"** failed to read NIfTI image from '%s'\n", fin);
    return 2;
  }

  printf("%dD, x=%d y=%d z=%d t=%d u=%d v=%d w=%d\n",
         nim->ndim, nim->nx, nim->ny, nim->nz,
         nim->nt, nim->nu, nim->nv, nim->nw);
  printf("nvox=%d nbyper=%d\n",
         nim->nvox, nim->nbyper);
  printf("%fD x=%f y=%f z=%f t=%f u=%f v=%f w=%f\n",
         nim->pixdim[0], nim->dx, nim->dy, nim->dz,
         nim->dt, nim->du, nim->dv, nim->dw);

  unsigned short *q = static_cast<unsigned short *>(nim->data);
  unsigned short max = 0, min = 0, mean = 0;
  unsigned long long sum = 0;

  for (int i = width*height*layer; i < width*height*(layer+1); i++) {
    sum += q[i];
//    printf("%u\n", q[i]);
    if (q[i] > max)
      max = q[i];
  }

  mean = sum / (width*height);
  printf("max=%u min=%u mean=%u\n", max, min, mean);

//===================================================================
//        suv_max_group = max(temp_img)*weight/(decay_factor*dose);
//        suv_mean_group = mean(temp_img)*weight/(decay_factor*dose);
//weight INPUT
//dose INPUT
//time INPUT
//half_life INPUT
//decay_factor  = 2^(-time*60/half_life);
//===================================================================

  int weight = 156;
  int dose = 156;
  int time = 16;
  int half_life = 15;
  int decay_factor = 2^(-time*60/half_life);
  printf("weight=%d decay_factor=%d dose=%d\n", weight, decay_factor, dose);

  int suv_max = max * weight / (decay_factor * dose);
  int suv_mean = mean * weight / (decay_factor * dose);
  printf("suv_max=%d suv_mean=%d\n", suv_max, suv_mean);

  unsigned short p[width*height];
  for (int i = 0; i < width*height; i++) {
    p[i] = q[width*height*layer + i] * 255 / max;
  }

  BMP Output;
  Output.SetSize(width, height);
  Output.SetBitDepth(24);

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      RGBApixel NewPixel;

      if (check_area(i, j) == 1) {
          NewPixel.Red = p[i*width + j];
          NewPixel.Green = p[i*width + j];
          NewPixel.Blue = p[i*width + j];
      } else {
          NewPixel.Red = 0;
          NewPixel.Green = 0;
          NewPixel.Blue = 0;
      }
      NewPixel.Alpha = 0;
      Output.SetPixel(i, j, NewPixel);
    }
  }

  Output.SetBitDepth(32);
  Output.WriteToFile("EasyBMPoutput32bpp.bmp");

  Output.SetBitDepth(24);
  Output.WriteToFile("EasyBMPoutput24bpp.bmp");

  Output.SetBitDepth(8);
  Output.WriteToFile("EasyBMPoutput8bpp.bmp");

  Output.SetBitDepth(4);
  Output.WriteToFile("EasyBMPoutput4bpp.bmp");

  Output.SetBitDepth(1);
  Output.WriteToFile("EasyBMPoutput1bpp.bmp");

  Output.SetBitDepth(24);
  Rescale(Output, 'p', 50);
  Output.WriteToFile("EasyBMPoutput24bpp_rescaled.bmp");

  /* and clean up memory */
  nifti_image_free(nim);

  return 0;
}