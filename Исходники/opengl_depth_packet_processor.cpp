void OpenGLDepthPacketProcessor::load11To16LutFromFile(const char* filename)
{
  ChangeCurrentOpenGLContext ctx(impl_->opengl_context_ptr);

  impl_->lut11to16.allocate(2048, 1);

  const unsigned char *data;
  size_t length;

  if(loadResource("11to16.bin", &data, &length))
  {
    std::copy(data, data + length, impl_->lut11to16.data);
    impl_->lut11to16.upload();
  }
  else
  {
    LOG_ERROR << "Loading 11to16 lut from resource '11to16.bin' failed!";
  }
}