/**
  Reads the ini file and returns the dictionary name.
  */
MetaInfo BibleQuoteDict::readInfo(QFile &file)
{
    const QString encoding = m_settings->encoding;
    QTextCodec *codec = QTextCodec::codecForName(encoding.toStdString().c_str());
    QTextDecoder *decoder = codec->makeDecoder();
    QByteArray byteline = file.readLine();
    QString line = decoder->toUnicode(byteline);
    file.close();
    MetaInfo info;
    info.setName(line.simplified());
    return info;
}