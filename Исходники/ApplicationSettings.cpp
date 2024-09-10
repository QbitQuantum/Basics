void ApplicationSettings::parse()
{
    QCommandLineParser parser;
    parser.setApplicationDescription(QObject::tr("i-score - An interactive sequencer for the intermedia arts."));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", QCoreApplication::translate("main", "Scenario to load."));

    QCommandLineOption noGUI("no-gui", QCoreApplication::translate("main", "Disable GUI"));
    parser.addOption(noGUI);
    QCommandLineOption noRestore("no-restore", QCoreApplication::translate("main", "Disable auto-restore"));
    parser.addOption(noRestore);

    QCommandLineOption autoplayOpt("autoplay", QCoreApplication::translate("main", "Auto-play the loaded scenario"));
    parser.addOption(autoplayOpt);

    parser.process(*qApp);

    const QStringList args = parser.positionalArguments();

    tryToRestore = !parser.isSet(noRestore);
    gui = !parser.isSet(noGUI);
    autoplay = parser.isSet(autoplayOpt) && args.size() == 1;

    if(!args.empty() && QFile::exists(args[0]))
    {
        loadList.push_back(args[0]);
    }
}