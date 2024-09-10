bool SqLiteStorage::migrateDatabaseDirectory( QDir oldDirectory, QDir newDirectory ) const
{
    if ( oldDirectory == newDirectory )
        return true;
    qDebug() << "Application::configure: migrating Charm database directory contents from"
             << oldDirectory.absolutePath() << "to" << newDirectory.absolutePath();

    oldDirectory.setFilter( QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot );
    Q_FOREACH ( const QString& entry, oldDirectory.entryList() )
        oldDirectory.rename( entry, newDirectory.path() + QDir::separator() + entry );

    QDir oldDirectoryParent( oldDirectory );
    oldDirectoryParent.cdUp();
    return oldDirectoryParent.rmpath( oldDirectory.dirName() );
}