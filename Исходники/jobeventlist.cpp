void JobEventList::setContent(const QString &content, const QString &userName,
                              QList<qint64> jobIds)
{
  m_xml = content;
  m_valid = true;

  MessageHandler handler;
  QXmlQuery query;
  query.setMessageHandler(&handler);
  JobEventListXmlReceiver receiver(query.namePool());
  query.setFocus(m_xml);

  if (jobIds.isEmpty()) {
    query.setQuery("/list/JobEvent");
  }
  else {
    QString xpath = "/list/JobEvent/jobID[";
    QListIterator<qint64> iter(jobIds);

    while (iter.hasNext()) {
      qint64 jobId = iter.next();
      xpath += QString("starts-with(text(), '%1')").arg(jobId);
      if (iter.hasNext())
        xpath += " or ";
    }

    xpath += "]/parent::node()";

    query.setQuery(xpath);
  }

  m_valid = query.evaluateTo(&receiver);

  m_jobEvents = receiver.jobEvents();
}