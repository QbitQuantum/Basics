bool KMailBox::isLocked() const
{
	QFileInfo lockFile(_file + QString(".lock"));

	return lockFile.exists();
}