KCHMNetworkReply::KCHMNetworkReply( const QNetworkRequest &request, const QUrl &url )
{
	setRequest( request );
	setOpenMode( QIODevice::ReadOnly );

	m_data = loadResource( url );
	m_length = m_data.length();

	setHeader( QNetworkRequest::ContentLengthHeader, QByteArray::number(m_data.length()) );
	QMetaObject::invokeMethod(this, "metaDataChanged", Qt::QueuedConnection);

	if ( m_length )
		QMetaObject::invokeMethod(this, "readyRead", Qt::QueuedConnection);

	QMetaObject::invokeMethod(this, "finished", Qt::QueuedConnection);
}