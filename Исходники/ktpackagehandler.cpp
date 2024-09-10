bool KTPackageHandler::compress(QuaZip *zip, const QString &path)
{
	QFile inFile;
	QuaZipFile outFile(zip);
	char c;
	
	QFileInfoList files= QDir(path).entryInfoList();
	
	foreach(QFileInfo file, files)
	{
		QString filePath = path+"/"+file.fileName();
		
		
		if ( file.fileName().startsWith(".") ) continue;
		
		if ( file.isDir() )
		{
			compress(zip, file.path()+"/"+file.fileName());
			continue;
		}
		
		inFile.setFileName(filePath);
		if(!inFile.open(QIODevice::ReadOnly)) 
		{
			dError() << "Error opening file " << inFile.fileName() << " : " << inFile.errorString();
			return false;
		}
		
		if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(stripRepositoryFromPath(filePath), stripRepositoryFromPath(filePath) ))) 
		{
			return false;
		}
		while(inFile.getChar(&c) && outFile.putChar(c));
		
		if(outFile.getZipError()!=UNZ_OK)
		{
			return false;
		}
		outFile.close();
		if(outFile.getZipError()!=UNZ_OK)
		{
			return false;
		}
		inFile.close();
	}