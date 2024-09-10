void QgsGpsDeviceDialog::writeDeviceSettings()
{
  QStringList deviceNames;
  QgsSettings settings;
  QString devPath = QStringLiteral( "/Plugin-GPS/devices/%1" );
  settings.remove( QStringLiteral( "/Plugin-GPS/devices" ) );

  std::map<QString, QgsGpsDevice *>::const_iterator iter;
  for ( iter = mDevices.begin(); iter != mDevices.end(); ++iter )
  {
    deviceNames.append( iter->first );
    QString wptDownload =
      iter->second->importCommand( QStringLiteral( "%babel" ), QStringLiteral( "-w" ), QStringLiteral( "%in" ), QStringLiteral( "%out" ) ).join( QStringLiteral( " " ) );
    QString wptUpload =
      iter->second->exportCommand( QStringLiteral( "%babel" ), QStringLiteral( "-w" ), QStringLiteral( "%in" ), QStringLiteral( "%out" ) ).join( QStringLiteral( " " ) );
    QString rteDownload =
      iter->second->importCommand( QStringLiteral( "%babel" ), QStringLiteral( "-r" ), QStringLiteral( "%in" ), QStringLiteral( "%out" ) ).join( QStringLiteral( " " ) );
    QString rteUpload =
      iter->second->exportCommand( QStringLiteral( "%babel" ), QStringLiteral( "-r" ), QStringLiteral( "%in" ), QStringLiteral( "%out" ) ).join( QStringLiteral( " " ) );
    QString trkDownload =
      iter->second->importCommand( QStringLiteral( "%babel" ), QStringLiteral( "-t" ), QStringLiteral( "%in" ), QStringLiteral( "%out" ) ).join( QStringLiteral( " " ) );
    QString trkUpload =
      iter->second->exportCommand( QStringLiteral( "%babel" ), QStringLiteral( "-t" ), QStringLiteral( "%in" ), QStringLiteral( "%out" ) ).join( QStringLiteral( " " ) );
    settings.setValue( devPath.arg( iter->first ) + "/wptdownload",
                       wptDownload );
    settings.setValue( devPath.arg( iter->first ) + "/wptupload", wptUpload );
    settings.setValue( devPath.arg( iter->first ) + "/rtedownload",
                       rteDownload );
    settings.setValue( devPath.arg( iter->first ) + "/rteupload", rteUpload );
    settings.setValue( devPath.arg( iter->first ) + "/trkdownload",
                       trkDownload );
    settings.setValue( devPath.arg( iter->first ) + "/trkupload", trkUpload );
  }
  settings.setValue( QStringLiteral( "/Plugin-GPS/devicelist" ), deviceNames );
}