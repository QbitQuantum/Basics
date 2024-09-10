bool ThresholdWholeSlideFilter::process() {
  std::vector<unsigned long long> dims = this->_input->getLevelDimensions(this->_processedLevel);
  double downsample = this->_input->getLevelDownsample(this->_processedLevel);

  MultiResolutionImageWriter writer;
  unsigned int outSamplesPerPixel = _input->getSamplesPerPixel();
  unsigned int inSamplesPerPixel = _input->getSamplesPerPixel();
  if (_component >= inSamplesPerPixel) {
    std::cerr << "ERROR: Selected component is larger than number of input components, fallback to all components" << std::endl;
    _component = -1;
  }
  if (_component >= 0 || _input->getSamplesPerPixel() == 1) {
    writer.setColorType(pathology::ColorType::Monochrome);
    outSamplesPerPixel = 1;
  } else {
    writer.setColorType(pathology::ColorType::Indexed);
    writer.setNumberOfIndexedColors(_input->getSamplesPerPixel());
  }
  writer.setCompression(pathology::Compression::LZW);
  writer.setDataType(pathology::DataType::UChar);
  writer.setInterpolation(pathology::Interpolation::NearestNeighbor);
  writer.setTileSize(512);
  std::vector<double> spacing = _input->getSpacing();
  if (!spacing.empty()) {
    spacing[0] *= downsample;
    spacing[1] *= downsample;
    writer.setSpacing(spacing);
  }
  if (writer.openFile(_outPath) != 0) {
    std::cerr << "ERROR: Could not open file for writing" << std::endl;
    return false;
  }
  writer.setProgressMonitor(_monitor);
  writer.writeImageInformation(dims[0], dims[1]);

  float* tile = new float[512 * 512 * _input->getSamplesPerPixel()];
  unsigned char* out_tile = new unsigned char[512 * 512 * outSamplesPerPixel];
  for (unsigned long long t_y = 0; t_y < dims[1]; t_y += 512) {
    for (unsigned long long t_x = 0; t_x < dims[0]; t_x += 512) {
      this->_input->getRawRegion<float>(static_cast<unsigned long long>(t_x*downsample), static_cast<unsigned long long>(t_y*downsample), 512, 512, this->_processedLevel, tile);
      for (unsigned int y = 0; y < 512; ++y) {
        for (unsigned int x = 0; x < 512; ++x) {
          for (unsigned int c = 0; c < _input->getSamplesPerPixel(); ++c) {
            if (c == _component) {
              float curVal = tile[y * 512 * inSamplesPerPixel + x * inSamplesPerPixel + c];
              if (curVal >= _lowerThreshold && curVal < _upperThreshold) {
                out_tile[y * 512 + x] = 1;
              }
              else {
                out_tile[y * 512 + x] = 0;
              }
            }
            else if (_component < 0) {
              float curVal = tile[y * 512 * inSamplesPerPixel + x * inSamplesPerPixel + c];
              if (curVal >= _lowerThreshold && curVal < _upperThreshold) {
                out_tile[y * 512 * inSamplesPerPixel + x * inSamplesPerPixel + c] = 1;
              }
              else {
                out_tile[y * 512 * inSamplesPerPixel + x * inSamplesPerPixel + c] = 0;
              }
            }
          }
        }
      }
      writer.writeBaseImagePart(reinterpret_cast<void*>(out_tile));
    }
  }
  writer.finishImage();

  delete[] tile;
  delete[] out_tile;
  return true;
}