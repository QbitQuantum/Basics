//! Creates a XML Writer from a file.
IXMLWriter* CFileSystem::createXMLWriter(const c8* filename)
{
	IWriteFile* file = createAndWriteFile(filename);
	IXMLWriter* writer = createXMLWriter(file);
	file->drop();
	return writer;
}