void ConfigSettingsWidget::on_cmdSetName_clicked()
{
     auto pConnection = ((MainListView*)FrmMain::instance()->mainWidget()->widget(MainView))->model.GetConnection(id);

     auto configDir = Utils::userApplicationDataDirectory() + "/config";

        //
	QDir dir;
    dir.rename(configDir + QLatin1String ("/") + pConnection->GetName(), configDir + QLatin1String ("/") + ui.txtName->text());

	QFile file;
    file.rename(configDir + QLatin1String ("/") + ui.txtName->text() + ("/") + pConnection->GetName() + (".ovpn"), configDir + QLatin1String ("/") + ui.txtName->text() + ("/") + ui.txtName->text() + (".ovpn"));

    QString sql (QString("UPDATE vpn SET \"vpn-name\" = '%1' WHERE \"vpn-id\" = %2")
                .arg(Crypt::encodePlaintext(Database::instance()->makeCleanValue(ui.txtName->text())))
                 .arg(id));

    Database::instance()->execute(sql);

    QString sql2 (QString("UPDATE vpn SET \"vpn-config\" = '%1' WHERE \"vpn-id\" = %2")
		.arg(Crypt::encodePlaintext(Database::instance()->makeCleanValue(configDir + QLatin1String ("/") + ui.txtName->text() + ("/") + ui.txtName->text() + (".ovpn"))))
		.arg(id));

    Database::instance()->execute(sql2);

    pConnection->SetName(ui.txtName->text());
    pConnection->SetConfigPath(configDir + QLatin1String ("/") + ui.txtName->text() + ("/") + ui.txtName->text() + (".ovpn"));
}