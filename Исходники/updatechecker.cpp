void UpdateChecker::resultReceiver(QString data)
{
    QDomDocument xml;

    qDebug() << data;

    xml.setContent(data);
    QDomElement productxml = xml.firstChildElement("product");
    if (productxml.isNull())
    {
        QMessageBox::critical(NULL, tr("Error"),
              tr("Could not check for updates. Wrong server response."));
        inProgress = false;
        return;
    }

    QDomElement urlxml = productxml.firstChildElement("url");

    QString url = urlxml.text();

    QDomNodeList versionsx = xml.elementsByTagName("version");
    if (versionsx.length()==0)
    {
        QMessageBox::critical(NULL, tr("Error"),
              tr("Could not check for updates. No versions found."));
        inProgress = false;
        return;
    }

    QString platform;

#ifdef Q_OS_WIN
    platform = "WIN";
#endif
#ifdef Q_OS_MAC
    platform = "MAC";
#endif
    if (platform.isEmpty()) platform = "UNIX";
    QStringList versions;
    QMap<QString, QUrl> urls;
    for(unsigned int i=0; i<versionsx.length(); i++)
    {
        QDomNode version = versionsx.at(i);
        QDomNode platformx = version.attributes().namedItem("platform");
        if (platformx.isNull()) continue;
        QString vpl = platformx.nodeValue();
        if ((vpl != platform) && (vpl != "ALL")) continue;
        QString ver = version.attributes().namedItem("id").nodeValue();
        versions.append(ver);
        QDomElement xurl = version.toElement().firstChildElement("url");
        urls[ver] = QUrl(xurl.text());
    }
    if (!versions.size())
    {
        if (!workSilent)
        QMessageBox::information(NULL, tr("No updates available"),
         tr("You have the latest version of this application."));
        inProgress = false;
        return;
    }
    qSort( versions.begin(), versions.end(), versionCompare); // I should write Version class with right compare
    QString version = versions.first();                       // operator and use QMap's auto sorting.
    if (versionCompare(version, QApplication::applicationVersion()))
    {
        QMessageBox msg;
        msg.addButton(tr("Yes"), QMessageBox::YesRole);
        msg.addButton(tr("No"), QMessageBox::NoRole);
        msg.setText(tr("Lastest version is %1. Do you want to update?").arg(version));
        msg.setWindowTitle(tr("Update available"));
        msg.exec();
        if (msg.buttonRole(msg.clickedButton()) == QMessageBox::YesRole)
        {
            QDesktopServices().openUrl(urls[version]);
        }
    }
    else
    {
        if (!workSilent)
        {
            QMessageBox::information(NULL, tr("No updates available"),
                       tr("You have the latest version of this application."));
        }
    }
    inProgress = false;
}