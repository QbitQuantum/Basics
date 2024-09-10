bool ArithmeticWholeSlideFilter::process() {
  std::vector<unsigned long long> dims = this->_input->getLevelDimensions(this->_processedLevel);
  double downsample = this->_input->getLevelDownsample(this->_processedLevel);

  MultiResolutionImageWriter writer;
  writer.setColorType(pathology::ColorType::Monochrome);
  writer.setCompression(pathology::Compression::LZW);
  writer.setDataType(pathology::DataType::UInt32);
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

  std::vector<unsigned char> labels;
  std::vector<std::string> stringLabels;
  core::split(_expression, stringLabels, ",");
  labels.resize(core::fromstring<unsigned int>(stringLabels.back()), 0);
  for (unsigned int i = 0; i < stringLabels.size() - 1; ++i) {
    labels[core::fromstring<unsigned int>(stringLabels[i])] = 1;
  }
  unsigned int* tile = new unsigned int[512 * 512];
  unsigned int* out_tile = new unsigned int[512 * 512];
  for (unsigned long long t_y = 0; t_y < dims[1]; t_y += 512) {
    for (unsigned long long t_x = 0; t_x < dims[0]; t_x += 512) {
      this->_input->getRawRegion<unsigned int>(static_cast<unsigned long long>(t_x*downsample), static_cast<unsigned long long>(t_y*downsample), 512, 512, this->_processedLevel, tile);
      for (unsigned int y = 0; y < 512; ++y) {
        for (unsigned int x = 0; x < 512; ++x) {
          float curVal = tile[y * 512 + x];
          if (curVal > 0 && labels[curVal]==0) {
            out_tile[y * 512 + x] = curVal;
          }
          else {
            out_tile[y * 512 + x] = 0;
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