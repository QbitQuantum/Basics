// Parameter List:
// Name - String displayed as name in Qt Creator
// qmake path - location of the qmake binary
// Type identifier - Desktop, Simulator, Symbian, ...
// SDK identifier - unique string to identify Qt version inside of the SDK (eg. desk473, simu11, ...)
// System Root Path
// sbs path
bool RegisterQtInCreatorV23Operation::performOperation()
{
    const QStringList args = arguments();

    if (args.count() < 4) {
        setError(InvalidArguments);
        setErrorString(tr("Invalid arguments in %0: %1 arguments given, minimum 4 expected.")
                        .arg(name()).arg(args.count()));
        return false;
    }

    PackageManagerCore *const core = qVariantValue<PackageManagerCore*>(value(QLatin1String("installer")));
    if (!core) {
        setError(UserDefinedError);
        setErrorString(tr("Needed installer object in \"%1\" operation is empty.").arg(name()));
        return false;
    }
    const QString &rootInstallPath = core->value(scTargetDir);
    if (rootInstallPath.isEmpty() || !QDir(rootInstallPath).exists()) {
        setError(UserDefinedError);
        setErrorString(tr("The given TargetDir %1 is not a valid/existing dir.").arg(rootInstallPath));
        return false;
    }

    const QString qtVersionsFileName = rootInstallPath
                                     + QLatin1String(QtVersionSettingsSuffixPath);
    int argCounter = 0;
    const QString &versionName = args.at(argCounter++);
    const QString &path = QDir::toNativeSeparators(args.value(argCounter++));
    const QString versionQmakePath = absoluteQmakePath(path);

    const QString &versionTypeIdentifier = args.at(argCounter++);
    const QString &versionSDKIdentifier = args.at(argCounter++);
    const QString &versionSystemRoot = fromNativeSeparatorsAllOS(args.value(argCounter++));
    const QString &versionSbsPath = fromNativeSeparatorsAllOS(args.value(argCounter++));

    ProjectExplorer::PersistentSettingsReader reader;
    int qtVersionCount = 0;
    QVariantMap map;
    if (reader.load(qtVersionsFileName)) {
        map = reader.restoreValues();
        qtVersionCount = map.value(QLatin1String("QtVersion.Count")).toInt();
        map.remove(QLatin1String("QtVersion.Count"));
        map.remove(QLatin1String("Version"));
    }

    ProjectExplorer::PersistentSettingsWriter writer;
    // Store old qt versions
    if (!map.isEmpty()) {
        for (int i = 0; i < qtVersionCount; ++i) {
            writer.saveValue(QString::fromLatin1("QtVersion.%1").arg(i)
                             , map[QLatin1String("QtVersion.") + QString::number(i)].toMap());
        }
        map.clear();
    }
    // Enter new version
    map.insert(QLatin1String("Id"), -1);
    map.insert(QLatin1String("Name"), versionName);
    map.insert(QLatin1String("QMakePath"), versionQmakePath);
    map.insert(QLatin1String("QtVersion.Type"),
               QLatin1String("Qt4ProjectManager.QtVersion.") + versionTypeIdentifier);
    map.insert(QLatin1String("isAutodetected"), true);
    map.insert(QLatin1String("autodetectionSource"),
               QLatin1String("SDK.") + versionSDKIdentifier);
    if (!versionSystemRoot.isEmpty())
        map.insert(QLatin1String("SystemRoot"), versionSystemRoot);
    if (!versionSbsPath.isEmpty())
        map.insert(QLatin1String("SBSv2Directory"), versionSbsPath);

    writer.saveValue(QLatin1String("QtVersion.") + QString::number(qtVersionCount), map);

    writer.saveValue(QLatin1String("Version"), 1);
    writer.saveValue(QLatin1String("QtVersion.Count"), qtVersionCount + 1);
    QDir().mkpath(QFileInfo(qtVersionsFileName).absolutePath());
    writer.save(qtVersionsFileName, QLatin1String("QtCreatorQtVersions"));

    return true;
}