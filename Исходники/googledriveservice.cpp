void GoogleDriveService::ForgetCredentials() {
  client_->ForgetCredentials();

  QSettings s;
  s.beginGroup(kSettingsGroup);

  s.remove("refresh_token");
  s.remove("user_email");
}