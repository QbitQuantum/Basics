void SharedWorkerProxy::documentDetached(Document* document)
{
    if (isClosing())
        return;
    // Remove the document from our set (if it's there) and if that was the last document in the set, mark the proxy as closed.
    MutexLocker lock(m_workerDocumentsLock);
    m_workerDocuments.remove(document);
    if (!m_workerDocuments.size())
        close();
}