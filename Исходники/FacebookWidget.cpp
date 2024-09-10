void FacebookWidget::saveApplicationState() {
    QDir configDir = QDir::home();
    if(!configDir.cd(".config/Socializer")) {
        qDebug()<<"Making path "<<QDir::cleanPath(".config/Socializer");
        configDir.mkpath(QDir::cleanPath(".config/Socializer"));
        configDir.cd(".config/Socializer");
    }

    QFile *configFile = new QFile(configDir.absoluteFilePath("WindowState"));
    configFile->open(QIODevice::WriteOnly);
    QDataStream configFileDataStream(configFile);
    configFileDataStream << saveGeometry();
    configFileDataStream << windowSizeIndex;
    configFile->close();
    configFile->deleteLater();

    if(themeRefreshTimer->isActive()) {
        QFile *themeFile = new QFile(configDir.absoluteFilePath("ThemeState"));
        themeFile->open(QIODevice::WriteOnly);
        QDataStream themeFileDataStream(themeFile);
        themeFileDataStream << themeParams;
        themeFile->close();
        themeFile->deleteLater();
    } else {
        configDir.remove("ThemeState");
    }
}