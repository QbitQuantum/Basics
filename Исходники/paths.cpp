	QString GetTemporaryName (const QString& pattern)
	{
		QTemporaryFile file (QDir::tempPath () + "/" + pattern);
		file.open ();
		QString name = file.fileName ();
		file.close ();
		file.remove ();
		return name;
	}