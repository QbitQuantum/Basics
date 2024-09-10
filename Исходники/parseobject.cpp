/** @brief Parse xml-data
 *----------------------------------------------------------------------------*/
void ParseObject::slotParse(const QByteArray &xmlData, const int &feedId,
                            const QDateTime &dtReply, const QString &codecName)
{
  if (mainApp->isSaveDataLastFeed()) {
    QFile file(mainApp->dataDir()  + "/lastfeed.dat");
    file.open(QIODevice::WriteOnly);
    file.write(xmlData);
    file.close();
  }

  qDebug() << "=================== parseXml:start ============================";

  db_.transaction();

  // extract feed id and duplicate news mode from feed table
  parseFeedId_ = feedId;
  QString feedUrl;
  duplicateNewsMode_ = false;
  QSqlQuery q(db_);
  q.setForwardOnly(true);
  q.exec(QString("SELECT duplicateNewsMode, xmlUrl FROM feeds WHERE id=='%1'").arg(parseFeedId_));
  if (q.first()) {
    duplicateNewsMode_ = q.value(0).toBool();
    feedUrl = q.value(1).toString();
  }

  // id not found (ex. feed deleted while updating)
  if (feedUrl.isEmpty()) {
    qWarning() << QString("Feed with id = '%1' not found").arg(parseFeedId_);
    emit signalFinishUpdate(parseFeedId_, false, 0, "0");
    db_.commit();
    return;
  }

  qDebug() << QString("Feed '%1' found with id = %2").arg(feedUrl).arg(parseFeedId_);

  // actually parsing
  feedChanged_ = false;

  bool codecOk = false;
  QString convertData(xmlData);
  QString feedType;
  QDomDocument doc;
  QString errorStr;
  int errorLine;
  int errorColumn;

  QRegExp rx("encoding=\"([^\"]+)",
             Qt::CaseInsensitive, QRegExp::RegExp2);
  int pos = rx.indexIn(xmlData);
  if (pos == -1) {
    rx.setPattern("encoding='([^']+)");
    pos = rx.indexIn(xmlData);
  }
  if (pos > -1) {
    QString codecNameT = rx.cap(1);
    qDebug() << "Codec name (1):" << codecNameT;
    QTextCodec *codec = QTextCodec::codecForName(codecNameT.toUtf8());
    if (codec) {
      convertData = codec->toUnicode(xmlData);
    } else {
      qWarning() << "Codec not found (1): " << codecNameT << feedUrl;
      if (codecNameT.contains("us-ascii", Qt::CaseInsensitive)) {
        QString str(xmlData);
        convertData = str.remove(rx.cap(0)+"\"");
      }
    }
  } else {
    if (!codecName.isEmpty()) {
      qDebug() << "Codec name (2):" << codecName;
      QTextCodec *codec = QTextCodec::codecForName(codecName.toUtf8());
      if (codec) {
        convertData = codec->toUnicode(xmlData);
        codecOk = true;
      } else {
        qWarning() << "Codec not found (2): " << codecName << feedUrl;
      }
    }
    if (!codecOk) {
      codecOk = false;
      QStringList codecNameList;
      codecNameList << "UTF-8" << "Windows-1251" << "KOI8-R" << "KOI8-U"
                    << "ISO 8859-5" << "IBM 866";
      foreach (QString codecNameT, codecNameList) {
        QTextCodec *codec = QTextCodec::codecForName(codecNameT.toUtf8());
        if (codec && codec->canEncode(xmlData)) {
          qDebug() << "Codec name (3):" << codecNameT;
          convertData = codec->toUnicode(xmlData);
          codecOk = true;
          break;
        }
      }
      if (!codecOk) {
        convertData = QString::fromLocal8Bit(xmlData);
      }
    }