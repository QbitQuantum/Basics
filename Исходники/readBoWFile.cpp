//**********************************************************************
//
// M A I N
//
//**********************************************************************
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QsLogging::initQsLog();
  if (argc<1) {    cerr << USAGE; exit(1); }
  readCommandLineArguments(argc,argv);
  if (param.help) { cerr << HELP; exit(1); }

  BOWLOGINIT;

  // read BoWFile and output documents

  std::ifstream fileIn(param.inputFile.c_str(),std::ifstream::binary);
  if (! fileIn)
  {
    cerr << "cannot open input file [" << param.inputFile << "]" << endl;
    exit(1);
  }
  BoWBinaryReader reader;
  try
  {
    reader.readHeader(fileIn);
  }
  catch (exception& e)
  {
    cerr << "Error: " << e.what() << endl;
    exit(1);
  }

  switch (reader.getFileType())  {

  case BOWFILE_TEXT: {

    LINFO << "ReadBoWFile: file contains a BoWText" << LENDL;
    BoWText text;
    reader.readBoWText(fileIn,text);

    switch (param.outputFormat) {
    case XML: {
      BoWXMLWriter writer(cout);
      writer.writeBoWText(&text,
                          param.useIterator,
                          param.useIndexIterator);
      break;
    }
    case BOWFILE_NOTYPE: {
      if (param.useIterator) {
        BoWTokenIterator it(text);
        while (! it.isAtEnd()) {
          cout << it.getElement()->getOutputUTF8String() << endl;
          it++;
        }
      }
      else if (param.useIndexIterator) {
        LINFO << "ReadBoWFile: call IndexElementIterator with maxCompoundSize=" << param.maxCompoundSize << LENDL;
        IndexElementIterator it(text,0,param.maxCompoundSize);
        while (! it.isAtEnd()) {
          cout << it.getElement() << endl;
          it++;
        }
      }
      else {
        cout << text << endl;
      }
      break;
    }
    default: cerr << "Error: output format not handled" << endl;
    }
    break;
  }
  case BOWFILE_SDOCUMENT:
  {
    LINFO << "ReadBoWFile: file contains a StructuredBoWDocument" << LENDL;
    BoWDocument* document=new BoWDocument();
    try
    {
      readSDocuments(fileIn, document, reader);
    }
    catch (exception& e) { cerr << "Error: " << e.what() << endl; }
    fileIn.close();
    delete document;
    break;
  }
/*
  case BOWFILE_DOCUMENT: {
    cerr << "ReadBoWFile: file contains a BoWDocument" << endl;
    BoWDocument* document=new BoWDocument();
    try
      {
        BoWXMLWriter::getInstance().writeBoWDocumentsHeader(cout);
        readDocuments(fileIn,document);
        BoWXMLWriter::getInstance().writeBoWDocumentsFooter(cout);
      }
    catch (exception& e) { cerr << "Error: " << e.what() << endl; }
    fileIn.close();
    delete document;
    break;
  }
  case BOWFILE_DOCUMENTST: {
    cerr << "ReadBoWFile: file contains a BoWDocumentST" << endl;
    BoWDocument* document=new BoWDocumentST();
    try {
      BoWXMLWriter::getInstance().writeBoWDocumentsHeader(cout);
      readDocuments(fileIn,document);
      BoWXMLWriter::getInstance().writeBoWDocumentsFooter(cout);
    }
    catch (exception& e) { cerr << "Error: " << e.what() << endl; }
    fileIn.close();
    delete document;
    break;
  }
*/  
  default: {
    cerr << "format of file " << reader.getFileTypeString() << " not managed"
         << endl;
    exit(1);
  }
  }
  return EXIT_SUCCESS;
}