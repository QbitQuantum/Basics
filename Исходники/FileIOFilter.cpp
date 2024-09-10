ccHObject* FileIOFilter::LoadFromFile(const QString& filename,
										CC_FILE_TYPES fType,
										bool alwaysDisplayLoadDialog/*=true*/,
										bool* coordinatesShiftEnabled/*=0*/,
										CCVector3d* coordinatesShift/*=0*/)
{
	//check file existence
    QFileInfo fi(filename);
    if (!fi.exists())
    {
        ccLog::Error(QString("[Load] File '%1' doesn't exist!").arg(filename));
        return 0;
    }

	//do we need to guess file format?
	if (fType == UNKNOWN_FILE)
	{
		//look for file extension (we trust Qt on this task)
		QString extension = QFileInfo(filename).suffix();
		if (extension.isEmpty())
		{
			ccLog::Error("[Load] Can't guess file format: no file extension");
			return 0;
		}

		//convert extension to file format
		fType = GuessFileFormatFromExtension(qPrintable(extension.toUpper()));

		//unknown extension?
		if (fType == UNKNOWN_FILE)
		{
			ccLog::Error(QString("[Load] Can't guess file format: unknown file extension '%1'").arg(extension));
			return 0;
		}
	}

	//get corresponding loader
	FileIOFilter* fio = CreateFilter(fType);
    if (!fio)
        return 0;

	//load file
    ccHObject* container = new ccHObject();
	CC_FILE_ERROR result = CC_FERR_NO_ERROR;
	try
	{
		result = fio->loadFile(	qPrintable(filename),
								*container,
								alwaysDisplayLoadDialog,
								coordinatesShiftEnabled,
								coordinatesShift);
	}
	catch(...)
	{
		ccLog::Warning("[I/O] Exception caught during file opening!");
		if (container)
			container->removeAllChildren();
		result = CC_FERR_CONSOLE_ERROR;
	}

	//we can release the loader instance
    delete fio;
    fio = 0;

	if (result != CC_FERR_NO_ERROR)
        DisplayErrorMessage(result,"loading",fi.baseName());
	else
		ccLog::Print(QString("[I/O] File '%1' loaded successfully").arg(fi.baseName()));

    unsigned childrenCount = container->getChildrenNumber();
    if (childrenCount != 0)
    {
		//we set the main container name as the full filename (with path)
        container->setName(QString("%1 (%2)").arg(fi.fileName()).arg(fi.absolutePath()));
        for (unsigned i=0;i<childrenCount;++i)
        {
            ccHObject* child = container->getChild(i);
			QString newName = child->getName();
			if (newName.startsWith("unnamed"))
			{
				//we automatically replace occurences of 'unnamed' in entities names by the base filename (no path, no extension)
				newName.replace(QString("unnamed"),fi.baseName());
				child->setName(newName);
			}
        }
    }
	else
    {
        delete container;
        container = 0;
    }

	return container;
}