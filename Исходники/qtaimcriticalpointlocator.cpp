  QString QTAIMCriticalPointLocator::temporaryFileName()
  {
    QTemporaryFile temporaryFile;
    temporaryFile.open();
    QString temporaryFileName=temporaryFile.fileName();
    temporaryFile.close();
    temporaryFile.remove();

    // wait for temporary file to be deleted
    QDir dir;
    do
    {
      // Nothing
    } while ( dir.exists(temporaryFileName) );

    return temporaryFileName;
  }