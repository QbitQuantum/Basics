void LYGithubManager::closeIssue(int issueNumber){
	if(!isAuthenticated() || repository_.isEmpty() || closeIssueReply_)
		return;

	LYGithubProductBacklogStatusLog::statusLog()->appendStatusMessage("Starting closeIssue request");

	QNetworkRequest request;

	QString commentURL = QString("https://api.github.com/repos/%1/issues/%2").arg(repository_).arg(issueNumber);
	request.setUrl(QUrl(commentURL));

	QString userInfo = userName_+":"+password_;
	QByteArray userData = userInfo.toLocal8Bit().toBase64();
	QString headerData = "Basic " + userData;
	request.setRawHeader("Authorization", headerData.toLocal8Bit());

	QVariantMap jdata;
	jdata["state"] = "closed";
	QJson::Serializer jserializer;
	QByteArray jsonData = jserializer.serialize(jdata);

	QBuffer *buffer = new QBuffer;
	buffer->setData(jsonData);
	buffer->open(QIODevice::ReadOnly);
	closeIssueReply_ = manager_->sendCustomRequest(request, "PATCH", buffer);
	buffer->setParent(closeIssueReply_);

	connect(closeIssueReply_, SIGNAL(readyRead()), this, SLOT(onCloseIssueReturned()));
}