void UrlOpener::openEmail(const QByteArray &email)
{
	QString client;
	bool useDefaultEMailClient = config_file.readBoolEntry("Chat", "UseDefaultEMailClient", true);
	if (useDefaultEMailClient)
		client = config_file.readEntry("Chat", "MailClient");

	QByteArray urlForDesktopServices;
	QByteArray urlForApplication;
	if (email.startsWith("mailto:"))
	{
		urlForDesktopServices = email;
		urlForApplication = email;
		urlForApplication.remove(0, 7);
	}
	else
	{
		urlForDesktopServices = "mailto:" + email;
		urlForApplication = email;
	}

	if (!openUrl(urlForDesktopServices, urlForApplication, client))
		MessageDialog::show("dialog-error", qApp->translate("@default", QT_TR_NOOP("Kadu")),
				qApp->translate("@default", QT_TR_NOOP("Could not spawn Mail client process. Check if the Mail client is functional")));
}