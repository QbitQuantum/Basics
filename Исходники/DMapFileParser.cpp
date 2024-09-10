  void DMapFileParser::parseRegularLine(
      std::string file_name, std::string line, uint32_t line_nr, DeviceInfoMapPointer dmap) {
    std::istringstream inStream;
    DeviceInfoMap::DeviceInfo deviceInfo;

    inStream.str(line);
    inStream >> deviceInfo.deviceName >> deviceInfo.uri >> deviceInfo.mapFileName;

    if(inStream) {
      std::string absPathToDMapFile = utilities::convertToAbsolutePath(file_name);
      std::string absPathToMapFile = absPathOfDMapContent(deviceInfo.mapFileName, file_name);
      deviceInfo.mapFileName = absPathToMapFile;
      deviceInfo.dmapFileName = absPathToDMapFile;
      deviceInfo.dmapFileLineNumber = line_nr;
      dmap->insert(deviceInfo);
    }
    else {
      std::istringstream inStream2;
      inStream2.str(line);
      inStream2 >> deviceInfo.deviceName >> deviceInfo.uri;

      if(inStream2) {
        std::string absPathToDMapFile = utilities::convertToAbsolutePath(file_name);
        deviceInfo.mapFileName = "";
        deviceInfo.dmapFileName = absPathToDMapFile;
        deviceInfo.dmapFileLineNumber = line_nr;
        dmap->insert(deviceInfo);
      }
      else {
        raiseException(file_name, line, line_nr);
      }
    }
  }