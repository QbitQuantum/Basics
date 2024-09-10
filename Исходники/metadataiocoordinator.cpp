    void MetadataIOCoordinator::readingFinishedHandler(bool ignoreBackups) {
        Q_ASSERT(m_CanProcessResults);
        m_CanProcessResults = false;

        const QHash<QString, ImportDataResult> &importResult = m_ReadingWorker->getImportResult();
        const QVector<Models::ArtworkMetadata*> &itemsToRead = m_ReadingWorker->getArtworksToImport();

        qDebug() << "Setting imported metadata...";
        int size = itemsToRead.size();
        for (int i = 0; i < size; ++i) {
            Models::ArtworkMetadata *metadata = itemsToRead.at(i);
            const QString &filepath = metadata->getFilepath();

            if (importResult.contains(filepath)) {
                const ImportDataResult &importResultItem = importResult.value(filepath);
                metadata->initialize(importResultItem.Title,
                                     importResultItem.Description,
                                     importResultItem.Keywords);
                metadata->setSize(importResultItem.Size);
            }
        }

        afterImportHandler(itemsToRead, ignoreBackups);

        qDebug() << "Metadata import finished";
        emit metadataReadingFinished();
    }