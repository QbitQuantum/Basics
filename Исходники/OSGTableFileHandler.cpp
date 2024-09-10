 TableDOMTransitPtr TableFileHandlerBase::forceRead(const BoostPath& FilePath)
 {
	 TableDOMRefPtr Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "TableFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType of a "txt" file (Forcing the document to be opened as a txt file)
	 TableFileTypeP TheFileType(getFileType("csv", TableFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "TableFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
			return TableDOMTransitPtr(NULL);
		 }
		 else
		 {
             //Read from the input stream
             startReadProgressThread(InputStream);
             Result = TheFileType->read(InputStream, FilePath.string());
             stopReadProgressThread();
             
			 InputStream.close();
		 }
	 }

	return TableDOMTransitPtr(Result);
 }