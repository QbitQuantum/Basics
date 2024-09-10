void SyncJournalDb::close()
{
    QMutexLocker locker(&_mutex);
    qDebug() << Q_FUNC_INFO << _dbFile;

    commitTransaction();

    _getFileRecordQuery.reset(0);
    _setFileRecordQuery.reset(0);
    _getDownloadInfoQuery.reset(0);
    _setDownloadInfoQuery.reset(0);
    _deleteDownloadInfoQuery.reset(0);
    _getUploadInfoQuery.reset(0);
    _setUploadInfoQuery.reset(0);
    _deleteUploadInfoQuery.reset(0);
    _deleteFileRecordPhash.reset(0);
    _deleteFileRecordRecursively.reset(0);
    _getErrorBlacklistQuery.reset(0);
    _setErrorBlacklistQuery.reset(0);

    _db.close();
    _avoidReadFromDbOnNextSyncFilter.clear();
}