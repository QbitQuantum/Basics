Response::Response(RequestParser p)
  : parser(p),
    mode(INTERNAL_ERROR),
    fileLength(-1),
    file(0),
    rangeStart(0),
    rangeEnd(0),
    offset(0),
    bytesRemaining(0)
{
  string target = parser.GetTarget();
  if (target == "") {
    mode = DIR_LIST;
    path = ".";
  } else if (target.find("..") != string::npos) {
    mode = ERROR_FILE_NOT_EXIST;
  } else {
    // Determine if the file exists, and if it is a directory.
    struct __stat64 buf;
    int result;
    result = _stat64(target.c_str(), &buf );
    if (result == -1) {
      cerr << "File not found" << std::endl;
      mode = ERROR_FILE_NOT_EXIST;
    } else if (result != 0) {
      mode = INTERNAL_ERROR;
    } else if (S_ISDIR(buf.st_mode)) {
      mode = DIR_LIST;
      path = parser.GetTarget();
    } else if (parser.IsRangeRequest() && !parser.IsLive()) {
      mode = GET_FILE_RANGE;
      path = parser.GetTarget();
      parser.GetRange(rangeStart, rangeEnd);
      if (rangeEnd == -1) {
        rangeEnd = buf.st_size;
      }
      fileLength = buf.st_size;
    } else {
      mode = GET_ENTIRE_FILE;
      path = parser.GetTarget();
      fileLength = buf.st_size;
    }
  }
}