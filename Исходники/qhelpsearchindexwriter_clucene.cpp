void QHelpSearchIndexWriter::run()
{
#if !defined(QT_NO_EXCEPTIONS)
    try {
#endif
        QMutexLocker mutexLocker(&mutex);

        if (m_cancel)
            return;

        const bool reindex = this->m_reindex;
        const QString collectionFile(this->m_collectionFile);

        mutexLocker.unlock();

        QHelpEngineCore engine(collectionFile, 0);
        if (!engine.setupData())
            return;

        const QLatin1String key("CluceneIndexedNamespaces");
        if (reindex)
            engine.setCustomValue(key, QLatin1String(""));

        QMap<QString, QDateTime> indexMap;
        const QLatin1String oldKey("CluceneSearchNamespaces");
        if (!engine.customValue(oldKey, QString()).isNull()) {
            // old style qhc file < 4.4.2, need to convert...
            const QStringList indexedNamespaces
                = engine.customValue(oldKey).toString()
                  .split(QLatin1String("|"), QString::SkipEmptyParts);
            foreach (const QString &nameSpace, indexedNamespaces)
                indexMap.insert(nameSpace, QDateTime());
            engine.removeCustomValue(oldKey);
        } else {
            QDataStream dataStream(engine.customValue(key).toByteArray());
            dataStream >> indexMap;
        }

        QString indexPath = m_indexFilesFolder;

        QFileInfo fInfo(indexPath);
        if (fInfo.exists() && !fInfo.isWritable()) {
            qWarning("Full Text Search, could not create index (missing permissions for '%s').",
                     qPrintable(indexPath));
            return;
        }

        emit indexingStarted();

        QCLuceneIndexWriter *writer = 0;
        QCLuceneStandardAnalyzer analyzer;
        const QStringList registeredDocs = engine.registeredDocumentations();

        QLocalSocket localSocket;
        localSocket.connectToServer(QString(QLatin1String("QtAssistant%1"))
                                    .arg(QLatin1String(QT_VERSION_STR)));

        QLocalServer localServer;
        bool otherInstancesRunning = true;
        if (!localSocket.waitForConnected()) {
            otherInstancesRunning = false;
            localServer.listen(QString(QLatin1String("QtAssistant%1"))
                               .arg(QLatin1String(QT_VERSION_STR)));
        }

        // check if it's locked, and if the other instance is running
        if (!otherInstancesRunning && QCLuceneIndexReader::isLocked(indexPath))
            QCLuceneIndexReader::unlock(indexPath);

        if (QCLuceneIndexReader::isLocked(indexPath)) {
            // poll unless indexing finished to fake progress
            while (QCLuceneIndexReader::isLocked(indexPath)) {
                mutexLocker.relock();
                if (m_cancel)
                    break;
                mutexLocker.unlock();
                this->sleep(1);
            }
            emit indexingFinished();
            return;
        }

        if (QCLuceneIndexReader::indexExists(indexPath) && !reindex) {
            foreach(const QString &namespaceName, registeredDocs) {
                mutexLocker.relock();
                if (m_cancel) {
                    emit indexingFinished();
                    return;
                }
                mutexLocker.unlock();

                if (!indexMap.contains(namespaceName)) {
                    // make sure we remove some partly indexed stuff
                    removeDocuments(indexPath, namespaceName);
                } else {
                    QString path = engine.documentationFileName(namespaceName);
                    if (indexMap.value(namespaceName)
                        < QFileInfo(path).lastModified()) {
                        // make sure we remove some outdated indexed stuff
                        indexMap.remove(namespaceName);
                        removeDocuments(indexPath, namespaceName);
                    }

                    if (indexMap.contains(namespaceName)) {
                        // make sure we really have content indexed for namespace
                        QCLuceneTermQuery query(QCLuceneTerm(NamespaceField, namespaceName));
                        QCLuceneIndexSearcher indexSearcher(indexPath);
                        QCLuceneHits hits = indexSearcher.search(query);
                        if (hits.length() <= 0)
                            indexMap.remove(namespaceName);
                    }
                }
            }