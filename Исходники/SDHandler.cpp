void SDHandler::_dirTest() {
#if DEBUG_LOGGING
  std::string path = "/sd/";
  _filenames = _read_directory(path);
  for(vector<std::string>::iterator it = _filenames.begin(); it < _filenames.end(); it++) {
    BT.printf("%s\n", (*it).c_str());
  }
#endif
}