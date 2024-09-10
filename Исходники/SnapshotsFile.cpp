QString SnapshotsFile::deleteSnapshot( const QString& sessionId, const QString& saveName ){
    QString result;
    QString fullName = saveName;
    if ( !saveName.endsWith( SUFFIX ) ){
        fullName = fullName + SUFFIX;
    }

    QString rootDir = _getRootDir( sessionId );
    QDirIterator it( rootDir, QDirIterator::Subdirectories );
    bool removed = false;
    while ( it.hasNext()){
        QString fileName = it.fileInfo().fileName();
        if ( fileName == fullName ){
            QDir dir;
            dir.remove( it.filePath());
            removed = true;
        }
        it.next();
    }
    if ( !removed ){
        result = "Unable to find snapshot "+saveName+" to remove.";
    }

    return result;
}