void
aBackup::cleanupTmpFiles(const QString& tmpDirName, QStringList *files)
{
	QFile file;
	QDir dir;
	file.setName(QDir::convertSeparators(tmpDirName+"/content.xml"));
	aLog::print(aLog::Debug, tr("aBackup delete file %1").arg(file.name()));
	file.remove();
	file.setName(QDir::convertSeparators(tmpDirName+"/busines-schema.cfg"));
	aLog::print(aLog::Debug, tr("aBackup delete file %1").arg(file.name()));
	file.remove();
	file.setName(QDir::convertSeparators(tmpDirName+"/META-INF/manifest.xml"));
	aLog::print(aLog::Debug, tr("aBackup delete file %1").arg(file.name()));
	file.remove();
	for(uint i=0; i<files->count(); i++)
	{
			file.setName(QDir::convertSeparators(tmpDirName + "/templates/"+ (*files)[i]));
			aLog::print(aLog::Debug, tr("aBackup delete file %1").arg(file.name()));
			file.remove();
	}
	aLog::print(aLog::Debug, tr("aBackup delete directory %1").arg(tmpDirName + "/META-INF"));
	dir.rmdir(QDir::convertSeparators(tmpDirName + "/META-INF"));
	aLog::print(aLog::Debug, tr("aBackup delete directory %1").arg(tmpDirName + "/templates"));
	dir.rmdir(QDir::convertSeparators(tmpDirName + "/templates"));
	aLog::print(aLog::Debug, tr("aBackup delete directory %1").arg(tmpDirName));
	dir.rmdir(QDir::convertSeparators(tmpDirName));
	aLog::print(aLog::Info, tr("aBackup cleanup temporary files"));

}