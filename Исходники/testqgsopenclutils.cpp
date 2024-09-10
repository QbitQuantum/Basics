void TestQgsOpenClUtils::testProgramSource()
{
  QgsOpenClUtils::setSourcePath( QDir::tempPath() );
  QTemporaryFile tmpFile( QDir::tempPath() + "/XXXXXX.cl" );
  tmpFile.open( );
  tmpFile.write( QByteArray::fromStdString( source( ) ) );
  tmpFile.flush();
  QString baseName = tmpFile.fileName().replace( ".cl", "" ).replace( QDir::tempPath(), "" );
  QVERIFY( ! QgsOpenClUtils::sourceFromBaseName( baseName ).isEmpty() );
}