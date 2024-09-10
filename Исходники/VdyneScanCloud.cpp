void VdyneScanCloud::readBinary(std::istream& stream) {
  BinaryStreamReader<std::istream> binaryStream(stream);
  size_t numScans;
  binaryStream >> mTimestamp >> mStartRotationAngle >> mEndRotationAngle
    >> numScans;
  for (size_t i = 0; i < numScans; ++i) {
    Scan scan;
    scan.readBinary(stream);
    mScans.push_back(scan);
  }
}