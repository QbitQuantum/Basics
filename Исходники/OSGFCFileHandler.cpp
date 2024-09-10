 FCFileHandlerBase::FCPtrStore FCFileHandlerBase::read(const BoostPath& FilePath)
 {
	 FCPtrStore Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "FCFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return Result;
	 }

	 std::string filename = initPathHandler(FilePath.string().c_str());

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType for this extension
	 FCFileTypeP TheFileType(getFileType(Extension, FCFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "FCFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return Result;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "FCFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
			return Result;
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

	 return Result;
 }