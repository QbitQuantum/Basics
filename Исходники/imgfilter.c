/** Make a gaussian convolution kernel.
\return Returns 0 when successful, otherwise <>0.
*/
int imgFillGaussKernel(
  /** Gaussian convolution kernel matrix[size][size], filled here */
  float **kernel,
  /** Gaussian S.D. in pixels (decimals are ok) */
  float stdev,
  /** Kernel dimension */
  int size
) {
  int x, y;
  float mx, my, v, ksum=0.0;

  if(kernel==NULL || size<3) return 1;
  if(stdev<0.0) return 2;
  if((size%2)==0) return 3; // size must be odd number

  v=stdev*stdev;
  for(x=0; x<size; x++) {
    mx = x - size/2; // note: ints on purpose
    for(y=0; y<size; y++) {
      my = y - size/2; // note: ints on purpose
      if(stdev>0) {
#if(0)  // Gaussian in the middle of pixel is calculated
        kernel[y][x] =
          (1.0/(2.0*M_PI*v)) * powf(M_E,-((mx*mx)+(my*my))/(2.0*v));
#else  // Pixel area is considered
        kernel[y][x] = 0.25
              *(erff((mx-0.5)/(stdev*M_SQRT2))-erff((mx+0.5)/(stdev*M_SQRT2)))
              *(erff((my-0.5)/(stdev*M_SQRT2))-erff((my+0.5)/(stdev*M_SQRT2)));
#endif
      } else {
        if(x==size/2 && y==size/2) kernel[y][x]=1.0; else kernel[y][x]=0.0;
      }
      ksum+=kernel[y][x];
    }
  }

  /* Ensure quantitativity with normalization;
     divide each kernel value by their sum */
  v=1.0/ksum;
  for(x=0; x<size; x++) for(y=0; y<size; y++) kernel[y][x]*=v;

  return 0;
}