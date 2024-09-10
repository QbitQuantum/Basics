void DirListingInfo::setContent(const QString &content)
{
  m_xml = content;
  m_valid = true;

  MessageHandler handler;
  QXmlQuery query;
  query.setMessageHandler(&handler);
  query.setFocus(m_xml);

  QString dir;
  query.setQuery("/DirListingInfo/currentDirectory/string()");
  m_valid = query.evaluateTo(&dir);

  if (!m_valid)
    return;

  m_currentDirectory = dir.trimmed();

  // Get the directories;
  FileInfoXmlReceiver dirReceiver(query.namePool());
  query.setQuery("/DirListingInfo/directories");
  m_valid = query.evaluateTo(&dirReceiver);

  if (!m_valid)
    return;

  m_directories = dirReceiver.fileInfos();

  // Get the files
  FileInfoXmlReceiver fileReceiver(query.namePool());
  query.setQuery("/DirListingInfo/files");
  m_valid = query.evaluateTo(&fileReceiver);

  if (!m_valid)
    return;

  m_files = fileReceiver.fileInfos();
}