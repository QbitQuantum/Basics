ScXMLDocument *
ScXMLDocument::readFile(const char * filename)
{
  ScXMLDocument * scxmldoc = NULL;

  if (strncmp(filename, "coin:", 5) == 0) { // is a "resource"
    //size_t buffersize = 0;
    SbByteBuffer buffer = CoinResources::get(filename);
    if (likely(buffer.isValid())) {
      scxmldoc = ScXMLDocument::readBuffer(buffer);
      if (scxmldoc) {
        scxmldoc->setFilename(filename);
      }
      return scxmldoc;
    }
  }

  boost::intrusive_ptr<cc_xml_doc> xmldoc(cc_xml_doc_new());
  if (unlikely(!cc_xml_doc_read_file_x(xmldoc.get(), filename))) {
    return NULL;
  }

  scxmldoc = ScXMLDocument::readXMLData(xmldoc.get());
  if (unlikely(!scxmldoc)) {
    return NULL;
  }

  scxmldoc->setFilename(filename);

  return scxmldoc;
}