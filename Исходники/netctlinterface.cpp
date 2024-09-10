/**
 * @fn connectToUnknownEssid
 */
InterfaceAnswer NetctlInterface::connectToUnknownEssid(const QString essid,
                                                       QMap<QString, QString> settings) const
{
    if (debug) qDebug() << PDEBUG;
    if (netctlCommand == nullptr) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not find library";
        return InterfaceAnswer::Error;
    }
    if (wpaCommand == nullptr) {
        if (debug) qDebug() << PDEBUG << ":" << "Could not find library";
        return InterfaceAnswer::Error;
    }

    // append settings
    QStringList interfaces = netctlCommand->getWirelessInterfaceList();
    if (interfaces.isEmpty()) return InterfaceAnswer::Error;
    settings[QString("Description")] = QString("'Automatically generated profile by Netctl GUI'");
    settings[QString("Interface")] = interfaces.first();
    settings[QString("Connection")] = QString("wireless");
    settings[QString("ESSID")] = QString("'%1'").arg(essid);
    settings[QString("IP")] = QString("dhcp");

    // save profile
    QString profile = QString("netctl-gui-%1").arg(essid);
    profile.remove(QChar('"')).remove(QChar('\''));
    if (createProfile(profile, settings) != InterfaceAnswer::True) return InterfaceAnswer::Error;

    // start it
    return startProfile(profile);
}