int UtcDaliPixelData02(void)
{
  TestApplication application;

  unsigned int width = 10u;
  unsigned int height = 10u;
  unsigned int bufferSize = width*height*Pixel::GetBytesPerPixel( Pixel::L8 );
  unsigned char* buffer = new unsigned char [ bufferSize ];
  buffer[0] = 'a';

  PixelData pixelData = PixelData::New( buffer, bufferSize, width, height, Pixel::L8, PixelData::DELETE_ARRAY );

  DALI_TEST_CHECK( pixelData);
  DALI_TEST_CHECK( pixelData.GetWidth() == width );
  DALI_TEST_CHECK( pixelData.GetHeight() == height );
  DALI_TEST_CHECK( pixelData.GetPixelFormat() == Pixel::L8 );

  END_TEST;
}