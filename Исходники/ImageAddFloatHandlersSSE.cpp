  void _Run(OutputPixelType aaOutput[ciHeight][ciWidth], InputPixelType_1 aaInput1[ciHeight][ciWidth], InputPixelType_2 aaInput2[ciHeight][ciWidth])
  {
    for (int iY = 0; iY < ciHeight; ++iY)
    {
      OutputPixelType   *pOutput = aaOutput[iY];
      InputPixelType_1  *pInput1 = aaInput1[iY];
      InputPixelType_2  *pInput2 = aaInput2[iY];

      for (int iX = 0; iX < ciWidth; iX += VectorWidth)
      {
        __m128 mmIn1 = _mm_loadu_ps( pInput1 + iX );
        __m128 mmIn2 = _mm_loadu_ps( pInput2 + iX );

        _mm_storeu_ps( pOutput + iX, _mm_add_ps(mmIn1, mmIn2) );
      }
    }
  }