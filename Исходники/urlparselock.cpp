UrlParseLock::~UrlParseLock() {
  QMutexLocker lock(&urlParseMutex);
  Q_ASSERT(parsingUrls.contains(m_url));
  Q_ASSERT(parsingUrls[m_url].first == QThread::currentThread());
  --parsingUrls[m_url].second;
  if(parsingUrls[m_url].second == 0)
    parsingUrls.remove(m_url);
}