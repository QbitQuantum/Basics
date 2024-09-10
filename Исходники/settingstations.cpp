void
SettingStations::okClicked()
{
    _config->stationsList(*_stationlist);
    _config->TemperatureUnit(ui->temperatureCombo->currentText().toStdString());
    _config->WindSpeedUnit(ui->windCombo->currentText().toStdString());
    _config->iconSet(ui->iconsetCombo->currentText().toStdString());
    _config->UpdateConnect(ui->updateCheck->isChecked());
    _config->UpdatePeriod(period_hash[ui->updateCombo->currentText()]);
    _config->saveConfig();

    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage message = QDBusMessage::createSignal("/org/meego/omweather",
                               "org.meego.omweather", "reload_config");
    bus.send(message);
    message = QDBusMessage::createMethodCall("org.meego.omweather","/org/meego/omweather",
                               "org.meego.omweather", "reload_config");
    bus.send(message);

}