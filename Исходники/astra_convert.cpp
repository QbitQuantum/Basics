const AstraVideoMode astra_convert(const openni::VideoMode& input)
{
  AstraVideoMode output;

  output.x_resolution_ = input.getResolutionX();
  output.y_resolution_ = input.getResolutionY();
  output.frame_rate_ = input.getFps();
  output.pixel_format_ = static_cast<PixelFormat>(input.getPixelFormat());

  return output;
}