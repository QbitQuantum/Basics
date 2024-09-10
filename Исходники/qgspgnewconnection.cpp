//! Autoconnected SLOTS *
void QgsPgNewConnection::accept()
{
  QgsSettings settings;
  QString baseKey = QStringLiteral( "/PostgreSQL/connections/" );
  settings.setValue( baseKey + "selected", txtName->text() );
  bool hasAuthConfigID = !mAuthSettings->configId().isEmpty();

  if ( !hasAuthConfigID && mAuthSettings->storePasswordIsChecked( ) &&
       QMessageBox::question( this,
                              tr( "Saving Passwords" ),
                              tr( "WARNING: You have opted to save your password. It will be stored in unsecured plain text in your project files and in your home directory (Unix-like OS) or user profile (Windows). If you want to avoid this, press Cancel and either:\n\na) Don't save a password in the connection settings — it will be requested interactively when needed;\nb) Use the Configuration tab to add your credentials in an HTTP Basic Authentication method and store them in an encrypted database." ),
                              QMessageBox::Ok | QMessageBox::Cancel ) == QMessageBox::Cancel )
  {
    return;
  }

  // warn if entry was renamed to an existing connection
  if ( ( mOriginalConnName.isNull() || mOriginalConnName.compare( txtName->text(), Qt::CaseInsensitive ) != 0 ) &&
       ( settings.contains( baseKey + txtName->text() + "/service" ) ||
         settings.contains( baseKey + txtName->text() + "/host" ) ) &&
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
  settings.setValue( baseKey + "/service", txtService->text() );
  settings.setValue( baseKey + "/host", txtHost->text() );
  settings.setValue( baseKey + "/port", txtPort->text() );
  settings.setValue( baseKey + "/database", txtDatabase->text() );
  settings.setValue( baseKey + "/username", mAuthSettings->storeUsernameIsChecked( ) ? mAuthSettings->username() : QString() );
  settings.setValue( baseKey + "/password", mAuthSettings->storePasswordIsChecked( ) && !hasAuthConfigID ? mAuthSettings->password() : QString() );
  settings.setValue( baseKey + "/authcfg", mAuthSettings->configId() );
  settings.setValue( baseKey + "/publicOnly", cb_publicSchemaOnly->isChecked() );
  settings.setValue( baseKey + "/geometryColumnsOnly", cb_geometryColumnsOnly->isChecked() );
  settings.setValue( baseKey + "/dontResolveType", cb_dontResolveType->isChecked() );
  settings.setValue( baseKey + "/allowGeometrylessTables", cb_allowGeometrylessTables->isChecked() );
  settings.setValue( baseKey + "/sslmode", cbxSSLmode->currentData().toInt() );
  settings.setValue( baseKey + "/saveUsername", mAuthSettings->storeUsernameIsChecked( ) ? "true" : "false" );
  settings.setValue( baseKey + "/savePassword", mAuthSettings->storePasswordIsChecked( ) && !hasAuthConfigID ? "true" : "false" );
  settings.setValue( baseKey + "/estimatedMetadata", cb_useEstimatedMetadata->isChecked() );
  settings.setValue( baseKey + "/projectsInDatabase", cb_projectsInDatabase->isChecked() );

  // remove old save setting
  settings.remove( baseKey + "/save" );

  QDialog::accept();
}