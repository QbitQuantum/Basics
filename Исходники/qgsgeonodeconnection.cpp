void QgsGeoNodeConnectionUtils::deleteConnection( const QString &name )
{
  QgsSettings settings;
  // Add Section manually
  settings.remove( QStringLiteral( "qgis/connections-geonode/" ) + name );
  settings.remove( QStringLiteral( "qgis/geonode/" ) + name );
}