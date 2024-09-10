void ImageAdd::_RunInt()
{
  const size_t cszIters = static_cast< size_t >( TEST_RUN_COUNT );

  printf("\n    Running \"_RunInt()\"  -  Image-Size = %4d x %4d\n", ciImageWidth, ciImageHeight);

  HandlerList   lstHandlers;

  AppendHandlerList( lstHandlers, ImageAddInt_GetScalarHandlers() );
  AppendHandlerList( lstHandlers, ImageAddInt_GetSSEHandlers()    );
  AppendHandlerList( lstHandlers, ImageAddInt_GetAVXHandlers()    );

  CREATE_IMAGE( InputImageType1, spInputImage1 );
  CREATE_IMAGE( InputImageType2, spInputImage2 );
  CREATE_IMAGE( OutputImageType, spOutputImage );

  ImageIO::LoadTestImage( *spInputImage1 );
  ImageIO::LoadTestImage( *spInputImage2 );

  for (auto itHandler : lstHandlers)
  {
    printf( "\n      Launch handler \"%10s\"  ->  ", itHandler->GetName().c_str() );

    double dTime = omp_get_wtime();

    for (size_t szIter = static_cast<size_t>(0); szIter < cszIters; ++szIter)
    {
      _mm256_zeroall();
      itHandler->Launch( spOutputImage, spInputImage1, spInputImage2 );
    }

    dTime = omp_get_wtime() - dTime;
    dTime = (dTime * 1000.) / static_cast< double >( cszIters );

    printf( "%10.6f ms", dTime );
  }


#ifdef CONFIG_CHECK_OUTPUT

  IMAGE_ADD_CHECK_OUTPUT( Int );

#endif


  printf("\n");
}