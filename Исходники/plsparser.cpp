bool PLSParser::TryMagic(const QByteArray& data) const {
  return data.toLower().contains("[playlist]");
}