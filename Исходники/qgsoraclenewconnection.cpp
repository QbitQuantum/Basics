void QgsOracleNewConnection::accept()
{
  QgsSettings settings;
  QString baseKey = QStringLiteral( "/Oracle/connections/" );
  settings.setValue( baseKey + QStringLiteral( "selected" ), txtName->text() );

  if ( chkStorePassword->isChecked() &&
       QMessageBox::question( this,
                              tr( "Saving Passwords" ),
                              tr( "WARNING: You have opted to save your password. It will be stored in plain text in your project files and in your home directory on Unix-like systems, or in your user profile on Windows. If you do not want this to happen, please press the Cancel button.\n" ),
                              QMessageBox::Ok | QMessageBox::Cancel ) == QMessageBox::Cancel )
  {
    return;
  }

  // warn if entry was renamed to an existing connection
  if ( ( mOriginalConnName.isNull() || mOriginalConnName.compare( txtName->text(), Qt::CaseInsensitive ) != 0 ) &&
       ( settings.contains( baseKey + txtName->text() + QStringLiteral( "/service" ) ) ||
         settings.contains( baseKey + txtName->text() + QStringLiteral( "/host" ) ) ) &&
       QMessageBox::question( this,
                              tr( "Save Connection" ),
                              tr( "Should the existing connection %1 be overwritten?" ).arg( txtName->text() ),
                              QMessageBox::Ok | QMessageBox::Cancel ) == QMessageBox::Cancel )
  {
    return;
  }

  // on rename delete the original entry first
  if ( !mOriginalConnName.isNull() && mOriginalConnName != txtName->text() )
  {
    settings.remove( baseKey + mOriginalConnName );
    settings.sync();
  }

  baseKey += txtName->text();
  settings.setValue( baseKey + QStringLiteral( "/database" ), txtDatabase->text() );
  settings.setValue( baseKey + QStringLiteral( "/host" ), txtHost->text() );
  settings.setValue( baseKey + QStringLiteral( "/port" ), txtPort->text() );
  settings.setValue( baseKey + QStringLiteral( "/username" ), chkStoreUsername->isChecked() ? txtUsername->text() : QString() );
  settings.setValue( baseKey + QStringLiteral( "/password" ), chkStorePassword->isChecked() ? txtPassword->text() : QString() );
  settings.setValue( baseKey + QStringLiteral( "/userTablesOnly" ), cb_userTablesOnly->isChecked() );
  settings.setValue( baseKey + QStringLiteral( "/geometryColumnsOnly" ), cb_geometryColumnsOnly->isChecked() );
  settings.setValue( baseKey + QStringLiteral( "/allowGeometrylessTables" ), cb_allowGeometrylessTables->isChecked() );
  settings.setValue( baseKey + QStringLiteral( "/estimatedMetadata" ), cb_useEstimatedMetadata->isChecked() ? QStringLiteral( "true" ) : QStringLiteral( "false" ) );
  settings.setValue( baseKey + QStringLiteral( "/onlyExistingTypes" ), cb_onlyExistingTypes->isChecked() ? QStringLiteral( "true" ) : QStringLiteral( "false" ) );
  settings.setValue( baseKey + QStringLiteral( "/includeGeoAttributes" ), cb_includeGeoAttributes->isChecked() ? QStringLiteral( "true" ) : QStringLiteral( "false" ) );
  settings.setValue( baseKey + QStringLiteral( "/saveUsername" ), chkStoreUsername->isChecked() ? QStringLiteral( "true" ) : QStringLiteral( "false" ) );
  settings.setValue( baseKey + QStringLiteral( "/savePassword" ), chkStorePassword->isChecked() ? QStringLiteral( "true" ) : QStringLiteral( "false" ) );
  settings.setValue( baseKey + QStringLiteral( "/dboptions" ), txtOptions->text() );
  settings.setValue( baseKey + QStringLiteral( "/dbworkspace" ), txtWorkspace->text() );
  settings.setValue( baseKey + QStringLiteral( "/schema" ), txtSchema->text() );

  QDialog::accept();
}