void GaussianBeamWindow::saveFile(const QString& path)
{
	QSettings settings;
	QString fileName = path;
	QString dir = settings.value("GaussianBeamWindow/lastDirectory", "").toString();

	if (fileName.isNull())
		fileName = QFileDialog::getSaveFileName(this, tr("Save File"), dir, "*.xml");
	if (fileName.isEmpty())
		return;
	if (!fileName.endsWith(".xml"))
		fileName += ".xml";

	if (writeFile(fileName))
	{
		setCurrentFile(fileName);
		statusBar()->showMessage(tr("File") + " " + QFileInfo(fileName).fileName() + " " + tr("saved"));
		settings.setValue("GaussianBeamWindow/lastDirectory", QFileInfo(fileName).path());
	}
}