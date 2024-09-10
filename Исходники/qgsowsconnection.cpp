void QgsOwsConnection::deleteConnection( const QString &service, const QString &name )
{
  QgsSettings settings;
  settings.remove( "qgis/connections-" + service.toLower() + '/' + name );
  settings.remove( "qgis/" + service + '/' + name );
}