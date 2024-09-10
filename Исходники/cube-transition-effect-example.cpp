Texture CubeTransitionApp::LoadStageFillingTexture( const char* filepath )
{
  ImageDimensions dimensions( Stage::GetCurrent().GetSize().x, Stage::GetCurrent().GetSize().y );
  BitmapLoader loader = BitmapLoader::New( filepath, dimensions, FittingMode::SCALE_TO_FILL );
  loader.Load();
  PixelData pixelData = loader.GetPixelData();
  Texture texture = Texture::New( TextureType::TEXTURE_2D, pixelData.GetPixelFormat(), pixelData.GetWidth(), pixelData.GetHeight() );
  texture.Upload( pixelData );
  return texture;
}