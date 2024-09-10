void ItemEncryptedLoader::terminateGpgProcess()
{
    if (m_gpgProcess == nullptr)
        return;
    QProcess *p = m_gpgProcess;
    m_gpgProcess = nullptr;
    p->terminate();
    p->waitForFinished();
    p->deleteLater();
    m_gpgProcessStatus = GpgNotRunning;
    updateUi();
}