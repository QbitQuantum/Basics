bool ExportCommon::download(ExportContext *ctx, QString url, QString to) {
	QString filePath = QDir::cleanPath(ctx->outputDir.absoluteFilePath(to));
	QFileInfo fi = QFileInfo(filePath);
	ctx->outputDir.mkpath(fi.dir().absolutePath());
	QFile file(filePath);
	if (file.exists())
		return true;
	if (file.open(QIODevice::WriteOnly)) {
		exportInfo("Downloading %s\n", url.toStdString().c_str());

		QUrl imageUrl(url);
		FileDownloader *m_pImgCtrl = new FileDownloader(imageUrl);

		QEventLoop loop;
		loop.connect(m_pImgCtrl, SIGNAL(downloaded()), &loop, SLOT(quit()));
		loop.exec();

		QByteArray data = m_pImgCtrl->downloadedData();

		delete m_pImgCtrl;

		if (data.length() > 0) {
			file.write(data);
			return true;
		} else
			exportError("Failed to download %s\n", url.toStdString().c_str());
	} else
		exportError("Can't open file %s\n", to.toStdString().c_str());
	return false;
}