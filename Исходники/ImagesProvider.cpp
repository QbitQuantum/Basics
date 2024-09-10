IImageProvider * ImagesProvider::create(const QString & source)
{
	if (PathIsDirectoryA(source.toStdString().c_str()) || IsSupported(source))
		return new ImagesProvider(source);
			
	return nullptr;
}