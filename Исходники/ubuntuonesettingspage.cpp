void UbuntuOneSettingsPage::LogoutClicked() {
  QSettings s;
  s.beginGroup(UbuntuOneService::kSettingsGroup);
  s.remove("user_email");
  s.remove("consumer_key");
  s.remove("consumer_secret");
  s.remove("token");
  s.remove("token_secret");

  ui_->login_state->SetLoggedIn(LoginStateWidget::LoggedOut);
}