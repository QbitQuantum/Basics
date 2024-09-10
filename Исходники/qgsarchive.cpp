bool QgsArchive::zip( const QString &filename )
{
  // create a temporary path
  QTemporaryFile tmpFile;
  tmpFile.open();
  tmpFile.close();

  // zip content
  if ( ! QgsZipUtils::zip( tmpFile.fileName(), mFiles ) )
  {
    QString err = QObject::tr( "Unable to zip content" );
    QgsMessageLog::logMessage( err, QStringLiteral( "QgsArchive" ) );
    return false;
  }

  // remove existing zip file
  if ( QFile::exists( filename ) )
    QFile::remove( filename );

  // save zip archive
  if ( ! tmpFile.rename( filename ) )
  {
    QString err = QObject::tr( "Unable to save zip file '%1'" ).arg( filename );
    QgsMessageLog::logMessage( err, QStringLiteral( "QgsArchive" ) );
    return false;
  }

  // keep the zip filename
  tmpFile.setAutoRemove( false );

  return true;
}