MPxFileTranslator::MFileKind 
XFileTranslator::identifyFile(	
	const MFileObject& fileName,
	const char* buffer,
	short size) const
{ 
    LPSTR extension = PathFindExtensionA(fileName.name().asChar());
    if(0==lstrcmpA(extension, ".x"))
	{
		return kIsMyFileType;
	}
	else
	{
		return kNotMyFileType; 
	}
}