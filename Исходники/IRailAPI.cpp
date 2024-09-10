ArrayListT<Trip *> * IRailAPI::testRoutePlanner(){
	result r = E_SUCCESS;
	String fileName(L"/Home/2.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	//AppLog("Read buffer size %d", buffer.GetLimit());
	r = file->Construct(fileName, L"r"); //for write: w or w+
	r = file->Read(buffer); //to write: file->Write *beware of the permission w instead of r
	delete file; //closes the file, there is no default close method for files, its gets closed when its scope is closed
	buffer.SetPosition(0);
	ArrayListT<Trip *> * test = createTripList(&buffer);
	//AppLog("completed trips");
	return test;
}