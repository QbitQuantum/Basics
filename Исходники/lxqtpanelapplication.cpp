LxQtPanelApplication::LxQtPanelApplication(int& argc, char** argv)
    : LxQt::Application(argc, argv, true)
{
    QCoreApplication::setApplicationName(QStringLiteral("lxqt-panel"));
    QCoreApplication::setApplicationVersion(LXQT_VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription(QStringLiteral("LXQt panel"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configFileOption(QStringList()
            << QStringLiteral("c") << QStringLiteral("config") << QStringLiteral("configfile"),
            QCoreApplication::translate("main", "Use alternate configuration file."),
            QCoreApplication::translate("main", "Configuration file"));
    parser.addOption(configFileOption);

    parser.process(*this);

    const QString configFile = parser.value(configFileOption);

    if (configFile.isEmpty())
        mSettings = new LxQt::Settings(QStringLiteral("panel"), this);
    else
        mSettings = new LxQt::Settings(configFile, QSettings::IniFormat, this);

    // This is a workaround for Qt 5 bug #40681.
    Q_FOREACH(QScreen* screen, screens())
    {
        connect(screen, &QScreen::destroyed, this, &LxQtPanelApplication::screenDestroyed);
    }