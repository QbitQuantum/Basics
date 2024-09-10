QString
HostDialog::getHostSpecification(void) const
{
    QString host = getHostName();
    bool need_separator = false;
    bool need_delimiter = false;

    if (hostLineEdit->isModified())
        host = hostLineEdit->text().trimmed();
    if (host.length() == 0)
        return QString::null;

    if (proxyLineEdit->isModified()) {
        QString proxy = proxyLineEdit->text().trimmed();
        if (proxy.length() > 0)
            host.prepend("@").prepend(proxy);
    }

    if (containerCheckBox->isChecked() ||
	authenticateCheckBox->isChecked())
	need_delimiter = true;

    if (need_delimiter)
	host.append("?");

    if (containerCheckBox->isChecked()) {
	QString container = containerLineEdit->text().trimmed();
	host.append("container=").append(container);
	need_separator = true;
    }

    if (authenticateCheckBox->isChecked()) {
	QString username = usernameLineEdit->text().trimmed();
	QString password = passwordLineEdit->text().trimmed();
	QString realm = realmLineEdit->text().trimmed();

	if (need_separator)
	    host.append("&");
	host.append("username="******"&password="******"&realm=").append(realm);
	need_separator = true;
    }
    return host;
}