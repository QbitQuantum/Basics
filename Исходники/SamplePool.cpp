int SamplePool::ImportSample(Path &path) {

	if (count_==MAX_PIG_SAMPLES) return -1 ;

	// construct target path

	std::string dpath="samples:" ;
	dpath+=path.GetName() ;
	Path dstPath(dpath.c_str()) ;

    // Opens files

	I_File *fin=FileSystem::GetInstance()->Open(path.GetPath().c_str(),"r") ;
	if (!fin) {
		Trace::Error("Failed to open input file %s",path.GetPath().c_str()) ;
		return -1;
	} ;
	fin->Seek(0,SEEK_END) ;
	long size=fin->Tell() ;
	fin->Seek(0,SEEK_SET) ;

	I_File *fout=FileSystem::GetInstance()->Open(dstPath.GetPath().c_str(),"w") ;
	if (!fout) {
		fin->Close() ;
		delete (fin) ;
		return -1 ;
	} ;

	// copy file to current project

	char buffer[IMPORT_CHUNK_SIZE] ;
	while (size>0) {
		int count=(size>IMPORT_CHUNK_SIZE)?IMPORT_CHUNK_SIZE:size ;
		fin->Read(buffer,1,count) ;
		fout->Write(buffer,1,count) ;
		size-=count ;
	} ;

	fin->Close() ;
	fout->Close() ;
	delete(fin) ;
	delete(fout) ;

	// now load the sample

	bool status=loadSample(dstPath.GetPath().c_str()) ;

	SetChanged() ;
	SamplePoolEvent ev ;
	ev.index_=count_-1 ;
	ev.type_=SPET_INSERT ;
	NotifyObservers(&ev) ;
	return status?(count_-1):-1 ;
};