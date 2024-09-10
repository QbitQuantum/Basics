void StratumClient::readyRead() {
  if (m_responseTimerId != -1) {
    killTimer(m_responseTimerId);
    m_responseTimerId = -1;
  }

  QTextStream dataStream(m_socket);
  for (QString line = dataStream.readLine(); !line.isEmpty(); line = dataStream.readLine()) {
    qDebug() << "<<<< " << line;
    QJsonParseError parseError;
    QJsonObject dataObject = QJsonDocument::fromJson(line.toUtf8(), &parseError).object();
    if (parseError.error == QJsonParseError::NoError) {
      processData(dataObject);
    } else {
      qDebug() << "Json parse error: " << parseError.errorString();
    }
  }
}