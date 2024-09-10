void IcqAccountMainSettings::saveSettings()
{
	bool createAccount = !m_account;
	if (createAccount) {
		QString uin = ui->uinEdit->text();
		if (uin.isEmpty())
			return;
		m_account = new IcqAccount(uin);
	}

	Config cfg = m_account->config();
	cfg.beginGroup("general");
	QString newPassword = ui->passwordEdit->text();
	if (!newPassword.isEmpty())
		cfg.setValue("passwd", newPassword, Config::Crypted);
	else
		cfg.remove("passwd");
	QString nick = ui->userNameEdit->text();
	if (!nick.isEmpty())
		cfg.setValue("nick", ui->userNameEdit->text());
	else
		cfg.remove("nick");
	cfg.endGroup();
	cfg.beginGroup("connection");
	cfg.setValue("ssl", ui->sslBox->isChecked());
	cfg.setValue("host", ui->serverBox->currentText());
	cfg.setValue("port", ui->portBox->value());
	cfg.endGroup();

	if (createAccount)
		IcqProtocol::instance()->addAccount(m_account);
}