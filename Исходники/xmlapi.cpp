int XmlApi::xmlreader_loadFile(const char *filename, XmlReaderCallback *only_this_object) {
  if (filename == NULL) return 0;
  String path;
  if(STRSTR(filename,"/") || STRSTR(filename,"\\")) {
    path=filename;
    char *p=(char *)path.getValue();
    *((char *)Std::scanstr_back(p,"/\\",p)+1)=0;
  }
  return XmlReader::loadFile(Std::filename(filename), path.vs(), only_this_object);
}