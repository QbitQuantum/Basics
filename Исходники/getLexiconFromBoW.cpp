//**********************************************************************
//
// M A I N
//
//**********************************************************************
int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QsLogging::initQsLog();
  if (argc<1) {
        cerr << USAGE;
        return EXIT_FAILURE;
    }
    QsLogging::initQsLog();
    readCommandLineArguments(argc,argv);
    if (param.help) {
        cerr << HELP;
        return EXIT_FAILURE;
    }


    string resourcesPath=getenv("LIMA_RESOURCES")==0?"/usr/share/apps/lima/resources":string(getenv("LIMA_RESOURCES"));
    string configDir=getenv("LIMA_CONF")==0?"/usr/share/config/lima":string(getenv("LIMA_CONF"));

    if ( (!param.language.size()) && (!param.codeFile.size()) ) {
        cerr << "no codefile nor language specified !" << endl;
        cerr << "Use e.g option '-l fre'." << endl;
        cerr << "Option '-h' gives full help" << endl;
        return EXIT_FAILURE;
    }
    else if ( param.language.size() ) {
        param.codeFile=resourcesPath+"/LinguisticProcessings/"+param.language+"/code-"+param.language+".xml";
    }

    cerr << "read proccodeManager from file " << param.codeFile << "..." << endl;
    PropertyCodeManager propcodemanager;
    propcodemanager.readFromXmlFile(param.codeFile);
    cerr << "get macroManager..." << endl;
    const PropertyManager& macroManager = propcodemanager.getPropertyManager("MACRO");
    const PropertyAccessor& propertyAccessor = macroManager.getPropertyAccessor();
    set<LinguisticCode> referenceProperties;
    for ( std::vector<string>::const_iterator macro = param.macro.begin() ;
            macro != param.macro.end() ; macro++ ) {
        cerr << "referenceProperties.insert(" << *macro << ")" << endl;
        LinguisticCode referenceProperty = macroManager.getPropertyValue(*macro);
        referenceProperties.insert(referenceProperty);
    }

    cerr << "referencePropertySet= ";
    set<LinguisticCode>::iterator propIt = referenceProperties.begin();
    if ( propIt != referenceProperties.end() ) {
        const std::string& symbol = macroManager.getPropertySymbolicValue(*propIt);
        cerr << symbol;
        propIt++;
    }
    for ( ; propIt != referenceProperties.end() ; propIt++ ) {
        const std::string& symbol = macroManager.getPropertySymbolicValue(*propIt);
        cerr << ", " << symbol;
    }
    cerr << endl;

    Lexicon lex;

    // read all files and count terms
    vector<string>::const_iterator
    file=param.inputFiles.begin(),
         file_end=param.inputFiles.end();
    for (;file!=file_end; file++) {

        ifstream fileIn((*file).c_str(), std::ifstream::binary);
        if (! fileIn) {
            cerr << "cannot open input file [" << *file << "]" << endl;
            continue;
        }
        BoWBinaryReader reader;
        try {
            reader.readHeader(fileIn);
        }
        catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
            return EXIT_FAILURE;
        }

        switch (reader.getFileType()) {
        case BOWFILE_TEXT: {
            cerr << "Build lexicon from BoWText [" << *file << "]" << endl;
            try {
                readBowFileText(fileIn,reader, lex, propertyAccessor, referenceProperties);
            }
            catch (exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        case BOWFILE_DOCUMENTST: {
            cerr << "ReadBoWFile: file contains a BoWDocumentST  -> not treated" << endl;
        }
        case BOWFILE_DOCUMENT: {
            cerr << "ReadBoWFile: build BoWdocument from  " << *file<< endl;
            BoWDocument* document=new BoWDocument();
            try {
                cerr << "ReadBoWFile: extract terms... " << endl;
                readDocuments(fileIn,document,reader, lex, macroManager, propertyAccessor, referenceProperties);
            }
            catch (exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            fileIn.close();
            delete document;
            break;
        }
        default: {
            cerr << "format of file " << reader.getFileTypeString() << " not managed"
                 << endl;
            return EXIT_FAILURE;
        }
        }
    }

    // output stream (default is 'cout')
    std::ostream *s_out;

    // Manage output
    if ( param.outputFilename.length() == 0) s_out=&std::cout;
    else s_out = new std::ofstream(param.outputFilename.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    // output lexicon
    Lexicon::const_iterator
    w=lex.begin(),
      w_end=lex.end();
    for (;w!=w_end; w++) {
        (*s_out) << Common::Misc::limastring2utf8stdstring((*w).second.second) << "|"
        << Common::Misc::limastring2utf8stdstring((*w).first) << "|"
        << (*w).second.first << endl;
    }

    // Close output file (if any)
    if (  param.outputFilename.length() != 0)
        dynamic_cast<std::ofstream*>(s_out)->close();

    return EXIT_SUCCESS;
}