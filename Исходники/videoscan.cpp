void VideoScannerThread::SetHosts(const QStringList &hosts)
{
    m_liveSGHosts.clear();
    QStringList::const_iterator iter = hosts.begin();
    for (; iter != hosts.end(); ++iter)
        m_liveSGHosts << iter->toLower();
}