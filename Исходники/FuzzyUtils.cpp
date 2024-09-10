void FuzzyUtils::AdaptativeSelectiveBackgroundModelUpdate(IplImage* CurrentImage, IplImage* BGImage, IplImage* OutputImage, IplImage* Integral, float seuil, float alpha)
{
  PixelUtils p;

  float beta = 0.0;
  float* CurentImagePixel = (float*) malloc(3*sizeof(float));
  float* BGImagePixel = (float*) malloc(3*sizeof(float));
  float* OutputImagePixel = (float*) malloc(3*sizeof(float));
  float* IntegralImagePixel = (float*) malloc(1*sizeof(float));
  float *Maximum = (float*) malloc(1*sizeof(float));
  float *Minimum = (float*) malloc(1*sizeof(float));

  p.ForegroundMaximum(Integral, Maximum, 1);
  p.ForegroundMinimum(Integral, Minimum, 1);

  for(int i = 0; i < CurrentImage->width; i++)
  {
    for(int j = 0; j < CurrentImage->height; j++)
    {
      p.GetPixel(CurrentImage, i, j, CurentImagePixel);
      p.GetPixel(BGImage, i, j, BGImagePixel);
      p.GetGrayPixel(Integral, i, j, IntegralImagePixel);
      
      beta = 1 - ((*IntegralImagePixel) - ((*Minimum / (*Minimum - *Maximum)) * (*IntegralImagePixel) - (*Minimum * (*Maximum) / (*Minimum - *Maximum))));
      
      for(int k = 0; k < 3; k++)
        *(OutputImagePixel + k) = beta * (*(BGImagePixel + k)) + (1 - beta) * (alpha * (*(CurentImagePixel+k)) + (1-alpha) * (*(BGImagePixel+k)));
      
      p.PutPixel(OutputImage, i, j, OutputImagePixel);
    }
  }

  free(CurentImagePixel);
  free(BGImagePixel);
  free(OutputImagePixel);
  free(IntegralImagePixel);
  free(Maximum);
  free(Minimum);
}