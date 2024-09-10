void LogData::fileChangedOnDisk( const QString& filename )
{
    LOG(logINFO) << "signalFileChanged " << filename.toStdString();

    QFileInfo info( indexingFileName_ );
    const auto currentFileId = getFileId( indexingFileName_ );

    const auto file_size = indexing_data_.getSize();
    LOG(logDEBUG) << "current indexed fileSize=" << file_size;
    LOG(logDEBUG) << "info file_->size()=" << info.size();
    LOG(logDEBUG) << "attached_file_->size()=" << attached_file_->size();
    LOG(logDEBUG) << "attached_file_id_ index " << attached_file_id_.fileIndex;
    LOG(logDEBUG) << "currentFileId index " << currentFileId.fileIndex;

    // In absence of any clearer information, we use the following size comparison
    // to determine whether we are following the same file or not (i.e. the file
    // has been moved and the inode we are following is now under a new name, if for
    // instance log has been rotated). We want to follow the name so we have to reopen
    // the file to ensure we are reading the right one.
    // This is a crude heuristic but necessary for notification services that do not
    // give details (e.g. kqueues)

    const bool isFileIdChanged = attached_file_id_ != currentFileId;

    if ( isFileIdChanged || ( info.size() != attached_file_->size() )
            || ( attached_file_->openMode() == QIODevice::NotOpen ) ) {

        LOG(logINFO) << "Inconsistent size, or file index, the file might have changed, re-opening";

        reOpenFile();

        // We don't force a (slow) full reindex as this routinely happens if
        // the file is appended quickly.
        // This means we can occasionally have false negatives (should be dealt with at
        // a lower level): e.g. if a new file is created with the same name as the old one
        // and with a size greater than the old one (should be rare in practice).
    }

    std::function<std::shared_ptr<LogDataOperation>()> newOperation;

    const auto real_file_size = attached_file_->size();

    if ( isFileIdChanged || real_file_size < file_size ) {
        fileChangedOnDisk_ = Truncated;
        LOG(logINFO) << "File truncated";
        newOperation = std::make_shared<FullIndexOperation>;
    }
    else if ( real_file_size == file_size ) {
        LOG(logINFO) << "No change in file";

        if ( keepFileClosed_ ) {
            QMutexLocker locker( &fileMutex_ );
            attached_file_->close();
        }
    }
    else if ( fileChangedOnDisk_ != DataAdded ) {
        fileChangedOnDisk_ = DataAdded;
        LOG(logINFO) << "New data on disk";
        newOperation = std::make_shared<PartialIndexOperation>;
    }

    if ( newOperation ) {
        enqueueOperation( newOperation() );
        lastModifiedDate_ = info.lastModified();
        emit fileChanged( fileChangedOnDisk_ );
    }
}