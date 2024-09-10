int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("kiconfinder"));
    app.setApplicationVersion(KICONTHEMES_VERSION_STRING);
    QCommandLineParser parser;
    parser.setApplicationDescription(app.translate("main", "Finds an icon based on its name"));
    parser.addPositionalArgument(QStringLiteral("iconname"), app.translate("main", "The icon name to look for"));
    parser.addHelpOption();

    parser.process(app);
    if(parser.positionalArguments().isEmpty())
        parser.showHelp();

    Q_FOREACH(const QString& iconName, parser.positionalArguments()) {
        const QString icon = KIconLoader::global()->iconPath(iconName, KIconLoader::Desktop /*TODO configurable*/, true);
        if ( !icon.isEmpty() ) {
            printf("%s\n", icon.toLocal8Bit().constData());
        } else {
            return 1; // error
        }
    }

    return 0;
}