GdbCoreEngine::~GdbCoreEngine()
{
    if (m_coreUnpackProcess) {
        m_coreUnpackProcess->blockSignals(true);
        m_coreUnpackProcess->terminate();
        m_coreUnpackProcess->deleteLater();
        m_coreUnpackProcess = 0;
        if (m_tempCoreFile.isOpen())
            m_tempCoreFile.close();
    }
    if (!m_tempCoreName.isEmpty()) {
        QFile tmpFile(m_tempCoreName);
        tmpFile.remove();
    }
}