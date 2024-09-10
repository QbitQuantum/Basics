PassRefPtr<SharedBuffer> SharedBuffer::createWithContentsOfFile(const String& fileName)
{
    if (fileName.isEmpty())
        return 0;

	EA::WebKit::FileSystem* fileSystem = EA::WebKit::GetFileSystem();
	EA::WebKit::FileSystem::FileObject fileObject = fileSystem->CreateFileObject();

	if(fileSystem->OpenFile(fileObject, fileName.utf8().data(), EA::WebKit::FileSystem::kRead))
	{
		Vector<char> buffer(fileSystem->GetFileSize(fileObject));
		fileSystem->ReadFile(fileObject,buffer.data(),buffer.size());
		fileSystem->DestroyFileObject(fileObject);
		return SharedBuffer::adoptVector(buffer);
	}
	
	fileSystem->DestroyFileObject(fileObject);
	return 0;

}