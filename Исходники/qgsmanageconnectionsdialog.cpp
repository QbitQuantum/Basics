void QgsManageConnectionsDialog::loadOWSConnections( const QDomDocument &doc, const QStringList &items, const QString &service )
{
  QDomElement root = doc.documentElement();
  if ( root.tagName() != "qgs" + service.toUpper() + "Connections" )
  {
    QMessageBox::information( this, tr( "Loading connections" ),
                              tr( "The file is not an %1 connections exchange file." ).arg( service ) );
    return;
  }

  QString connectionName;
  QSettings settings;
  settings.beginGroup( "/Qgis/connections-" + service.toLower() );
  QStringList keys = settings.childGroups();
  settings.endGroup();
  QDomElement child = root.firstChildElement();
  bool prompt = true;
  bool overwrite = true;

  while ( !child.isNull() )
  {
    connectionName = child.attribute( "name" );
    if ( !items.contains( connectionName ) )
    {
      child = child.nextSiblingElement();
      continue;
    }

    // check for duplicates
    if ( keys.contains( connectionName ) && prompt )
    {
      int res = QMessageBox::warning( this,
                                      tr( "Loading connections" ),
                                      tr( "Connection with name '%1' already exists. Overwrite?" )
                                      .arg( connectionName ),
                                      QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll | QMessageBox::Cancel );

      switch ( res )
      {
        case QMessageBox::Cancel:
          return;
        case QMessageBox::No:
          child = child.nextSiblingElement();
          continue;
        case QMessageBox::Yes:
          overwrite = true;
          break;
        case QMessageBox::YesToAll:
          prompt = false;
          overwrite = true;
          break;
        case QMessageBox::NoToAll:
          prompt = false;
          overwrite = false;
          break;
      }
    }

    if ( keys.contains( connectionName ) && !overwrite )
    {
      child = child.nextSiblingElement();
      continue;
    }

    // no dups detected or overwrite is allowed
    settings.beginGroup( "/Qgis/connections-" + service.toLower() );
    settings.setValue( QString( "/" + connectionName + "/url" ) , child.attribute( "url" ) );
    settings.setValue( QString( "/" + connectionName + "/ignoreGetMapURI" ), child.attribute( "ignoreGetMapURI" ) == "true" );
    settings.setValue( QString( "/" + connectionName + "/ignoreGetFeatureInfoURI" ), child.attribute( "ignoreGetFeatureInfoURI" ) == "true" );
    settings.setValue( QString( "/" + connectionName + "/ignoreAxisOrientation" ), child.attribute( "ignoreAxisOrientation" ) == "true" );
    settings.setValue( QString( "/" + connectionName + "/invertAxisOrientation" ), child.attribute( "invertAxisOrientation" ) == "true" );
    settings.setValue( QString( "/" + connectionName + "/referer" ), child.attribute( "referer" ) );
    settings.setValue( QString( "/" + connectionName + "/smoothPixmapTransform" ), child.attribute( "smoothPixmapTransform" ) == "true" );
    settings.endGroup();

    if ( !child.attribute( "username" ).isEmpty() )
    {
      settings.beginGroup( "/Qgis/" + service.toUpper() + "/" + connectionName );
      settings.setValue( "/username", child.attribute( "username" ) );
      settings.setValue( "/password", child.attribute( "password" ) );
      settings.endGroup();
    }
    child = child.nextSiblingElement();
  }
}