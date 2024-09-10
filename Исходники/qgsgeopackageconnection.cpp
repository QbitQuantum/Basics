void QgsGeoPackageConnection::deleteConnection( const QString &name )
{
  QgsSettings settings;
  settings.remove( QStringLiteral( "%1/%2" ).arg( connectionsPath(), name ) );
}