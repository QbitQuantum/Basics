void XtionDepthDriverImpl::open()
{
  if(_device.isValid()) return;
  
  Status rc = _device.open(ANY_DEVICE);
  if(rc != STATUS_OK) {
    throw Exception(std::string("Open the device failed with\n")
      + OpenNI::getExtendedError());
  }
  _device.open(ANY_DEVICE);

  if(!_device.getSensorInfo(SENSOR_DEPTH)) {
    _device.close();
    throw Exception("Device has no depth sensor!");
  }

  rc = _stream.create(_device, SENSOR_DEPTH);
  if(rc != STATUS_OK) {
    _device.close();
    throw Exception(std::string("Create the depth stream failed with\n")
      + OpenNI::getExtendedError());
  }

  VideoMode mode = _stream.getVideoMode();
  mode.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);

  rc = _stream.setVideoMode(mode);
  if(rc != STATUS_OK) {
      throw Exception(std::string("Set the pixel format to "
          "PIXEL_FORMAT_DEPTH_1_MM failed with\n")
          + OpenNI::getExtendedError());
  }

  rc = _stream.start();
  if(rc != STATUS_OK) {
    _stream.destroy();
    _device.close();

    throw Exception(std::string("Starting the depth stream failed with\n")
      + OpenNI::getExtendedError());
  }

  rc = _stream.addNewFrameListener(this);
  if(rc != STATUS_OK) {
    _stream.stop();
    _stream.destroy();
    _device.close();

    throw Exception(std::string("Adding the frame listener failed with\n")
      + OpenNI::getExtendedError());
  }
}