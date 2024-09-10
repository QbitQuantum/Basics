//! Autoconnected SLOTS *
void QgsNewOgrConnection::accept()
{
  QgsSettings settings;
  QString baseKey = '/' + cmbDatabaseTypes->currentText() + "/connections/";
  settings.setValue( baseKey + "selected", txtName->text() );

  // warn if entry was renamed to an existing connection
  if ( ( mOriginalConnName.isNull() || mOriginalConnName != txtName->text() ) &&
       settings.contains( baseKey + txtName->text() + "/host" ) &&
       QMessageBox::question( this,
                              tr( "Save Connection" ),
                              tr( "Should the existing connection %1 be overwritten?" ).arg( txtName->text() ),
                              QMessageBox::Ok | QMessageBox::Cancel ) == QMessageBox::Cancel )
  {
    return;
  }

  // on rename delete original entry first
  if ( !mOriginalConnName.isNull() && mOriginalConnName != txtName->text() )
  {
    settings.remove( baseKey + mOriginalConnName );
  }

  baseKey += txtName->text();
  settings.setValue( baseKey + "/host", txtHost->text() );
  settings.setValue( baseKey + "/database", txtDatabase->text() );
  settings.setValue( baseKey + "/port", txtPort->text() );
  settings.setValue( baseKey + "/username", mAuthSettingsDatabase->storeUsernameIsChecked() ? mAuthSettingsDatabase->username() : QLatin1String( "" ) );
  settings.setValue( baseKey + "/password", mAuthSettingsDatabase->storePasswordIsChecked() ? mAuthSettingsDatabase->password() : QLatin1String( "" ) );
  settings.setValue( baseKey + "/store_username", mAuthSettingsDatabase->storeUsernameIsChecked() ? "true" : "false" );
  settings.setValue( baseKey + "/store_password", mAuthSettingsDatabase->storePasswordIsChecked() ? "true" : "false" );
  settings.setValue( baseKey + "/configid", mAuthSettingsDatabase->configId() );

  QDialog::accept();
}