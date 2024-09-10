void Shoter::onButtonSendClicked()
{
	/*Create file */
	QDate date = QDate::currentDate();
	QString name_file = date.toString();
	QString savedFile = name_file+".png";
	QTemporaryFile file;
	file.setFileName(savedFile);
	if (!m_screenshot.save(&file)) {
		qDebug("file is not saved");
		exit(1);
	}
	// qDebug()<<file.fileName();
	QFile *openFile = new QFile(savedFile);
	openFile->open(QIODevice::ReadOnly);
	QHttpMultiPart *multi = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	/* Upload to ipix.su */
	if (ui->comboBox->currentIndex()== 0) {
		QHttpPart file;
		file.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("image/png"));
		file.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name=\"file\"; filename=\""+savedFile+"\""));
		file.setBodyDevice(openFile);
		openFile->setParent(multi);
		multi->append(file);
		this->upload("http://ipix.su/api/upload",multi);
		/* upload to pix.academ.org */
	} else if (ui->comboBox->currentIndex() == 1) {
		QHttpPart action;
		action.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("name=\"action\""));
		action.setBody("upload_image");
		QHttpPart image;
		image.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
		image.setHeader(QNetworkRequest::ContentDispositionHeader,
						QVariant("form-data; name=\"image\"; filename=\""+savedFile+"\""));
		image.setBodyDevice(openFile);
		openFile->setParent(multi);
		multi->append(action);
		multi->append(image);
		upload("http://pix.academ.org", multi);
		/* Upload to ompldr.org*/
	} else if (ui->comboBox->currentIndex() == 2) {
		QHttpPart file1;
		file1.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
		file1.setHeader(QNetworkRequest::ContentDispositionHeader,
						QVariant("form-data; name=\"file1\"; filename=\""+savedFile+"\""));
		file1.setBodyDevice(openFile);
		openFile->setParent(multi);
		multi->append(file1);
		upload("http://ompldr.org/upload", multi);
	}
}