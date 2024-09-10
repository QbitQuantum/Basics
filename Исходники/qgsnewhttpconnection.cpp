void QgsNewHttpConnection::accept()
{
  QgsSettings settings;
  QString key = mBaseKey + txtName->text();
  QString credentialsKey = "qgis/" + mCredentialsBaseKey + '/' + txtName->text();

  if ( !validate() )
    return;

  // on rename delete original entry first
  if ( !mOriginalConnName.isNull() && mOriginalConnName != key )
  {
    settings.remove( mBaseKey + mOriginalConnName );
    settings.remove( "qgis/" + mCredentialsBaseKey + '/' + mOriginalConnName );
    settings.sync();
  }

  QUrl url( urlTrimmed() );
  settings.setValue( key + "/url", url.toString() );

  QString wfsKey = wfsSettingsKey( mBaseKey, txtName->text() );
  QString wmsKey = wmsSettingsKey( mBaseKey, txtName->text() );

  if ( mTypes & ConnectionWfs )
  {
    settings.setValue( wfsKey + "/ignoreAxisOrientation", cbxWfsIgnoreAxisOrientation->isChecked() );
    settings.setValue( wfsKey + "/invertAxisOrientation", cbxWfsInvertAxisOrientation->isChecked() );
  }
  if ( mTypes & ConnectionWms || mTypes & ConnectionWcs )
  {
    settings.setValue( wmsKey + "/ignoreAxisOrientation", cbxWmsIgnoreAxisOrientation->isChecked() );
    settings.setValue( wmsKey + "/invertAxisOrientation", cbxWmsInvertAxisOrientation->isChecked() );

    settings.setValue( wmsKey + "/ignoreGetMapURI", cbxIgnoreGetMapURI->isChecked() );
    settings.setValue( wmsKey + "/smoothPixmapTransform", cbxSmoothPixmapTransform->isChecked() );

    int dpiMode = 0;
    switch ( cmbDpiMode->currentIndex() )
    {
      case 0: // all => QGIS|UMN|GeoServer
        dpiMode = 7;
        break;
      case 1: // off
        dpiMode = 0;
        break;
      case 2: // QGIS
        dpiMode = 1;
        break;
      case 3: // UMN
        dpiMode = 2;
        break;
      case 4: // GeoServer
        dpiMode = 4;
        break;
    }

    settings.setValue( wmsKey + "/dpiMode", dpiMode );

    settings.setValue( wmsKey + "/referer", txtReferer->text() );
  }
  if ( mTypes & ConnectionWms )
  {
    settings.setValue( wmsKey + "/ignoreGetFeatureInfoURI", cbxIgnoreGetFeatureInfoURI->isChecked() );
  }
  if ( mTypes & ConnectionWfs )
  {
    QString version = QStringLiteral( "auto" );
    switch ( cmbVersion->currentIndex() )
    {
      case 0:
        version = QStringLiteral( "auto" );
        break;
      case 1:
        version = QStringLiteral( "1.0.0" );
        break;
      case 2:
        version = QStringLiteral( "1.1.0" );
        break;
      case 3:
        version = QStringLiteral( "2.0.0" );
        break;
    }
    settings.setValue( wfsKey + "/version", version );

    settings.setValue( wfsKey + "/maxnumfeatures", txtMaxNumFeatures->text() );

    settings.setValue( wfsKey + "/pagesize", txtPageSize->text() );
    settings.setValue( wfsKey + "/pagingenabled", cbxWfsFeaturePaging->isChecked() );
  }

  settings.setValue( credentialsKey + "/username", mAuthSettings->username() );
  settings.setValue( credentialsKey + "/password", mAuthSettings->password() );

  settings.setValue( credentialsKey + "/authcfg", mAuthSettings->configId() );

  settings.setValue( mBaseKey + "/selected", txtName->text() );

  QDialog::accept();
}