void ResetWindow::doReset()
{
	QDir dir = QDir::home();
	dir.cd(".WebRender");
	if(clearCacheCheckBox->checkState() == Qt::Checked)
	{
		dir.cd("Cache");
		deleteDir(dir.absolutePath());
		dir.cdUp();
	}
	if(clearCookiesCheckBox->checkState() == Qt::Checked)
	{
		dir.cd("Cookies");
		deleteDir(dir.absolutePath());
		dir.cdUp();
		dir.cd("LocalStorage");
		deleteDir(dir.absolutePath());
		dir.cdUp();
		dir.cd("OfflineStorage");
		deleteDir(dir.absolutePath());
		dir.cdUp();
	}
	if(clearHistoryCheckBox->checkState() == Qt::Checked)
		dir.remove("historyFile");
	if(clearBookmarksCheckBox->checkState() == Qt::Checked)
		dir.remove("bookmarksFile");
	if(clearPreferencesCheckBox->checkState() == Qt::Checked)
		dir.remove("preferencesFile");
}