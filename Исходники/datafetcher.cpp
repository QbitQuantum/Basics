void DataFetcher::fetchWorksheet(const QDate &startDate, const QDate &endDate)
{
	// Cleanup
	m_workLog.clear();
	m_lastError.clear();
	if(m_reply != NULL)
	{
		QNetworkReply* oldReply = m_reply;
		m_reply = NULL;

		oldReply->abort();
		oldReply->deleteLater();
	}

	if(m_credentialsProvider != NULL && (m_login.isNull() || m_password.isNull()))
	{
		QString newLogin, newPassword;
		if(m_credentialsProvider->getCredentials(&newLogin, &newPassword))
		{
			m_login = newLogin;
			m_password = newPassword;
		}
	}

	QUrl url;
	url.setScheme("https");
	url.setHost(m_host);
	url.setPath("rest/timesheet-gadget/1.0/raw-timesheet.json");
	url.addQueryItem("userId", m_login);

	static const QLocale locale(QLocale::English, QLocale::UnitedKingdom);
	static const QString jiraDateFormat("dd/MMM/yyyy");
	url.addQueryItem("startDate", locale.toString(startDate, jiraDateFormat));
	url.addQueryItem("endDate", locale.toString(endDate, jiraDateFormat));

	const QByteArray authorization = "Basic " + QString("%1:%2").arg(m_login).arg(m_password).toUtf8().toBase64();


	QNetworkRequest req;
	req.setUrl(url);
	req.setRawHeader("Authorization", authorization);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	m_reply = m_manager->get(req);
	connect(m_reply, SIGNAL(finished()), SLOT(processReply()));
}