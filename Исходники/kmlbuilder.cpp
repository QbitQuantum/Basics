/*
 * Move the images to the images folder.
 */
bool relocateImages(void)
{
	bool status = 1;
	QStringList filters;
	filters << "*.png";

	fileDir[ROOT]->setNameFilters(filters);
	QDirIterator iterator(*fileDir[ROOT]);
	QFile *file;
	QString *name;

	while(iterator.hasNext() && status)
	{
		file = new QFile(iterator.next());
		name = new QString(file->fileName());
		name->remove(0, 
		     name->lastIndexOf(QString(fileDir[ROOT]->separator()))+1);
		status = file->copy(fileDir[IMAGES]->absolutePath() +
			fileDir[IMAGES]->separator() + *name);
		file->remove();
		delete file;
		delete name;
	}

	return status;
}