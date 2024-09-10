void AssetServer::run() {
    ThreadedAssignment::commonInit(ASSET_SERVER_LOGGING_TARGET_NAME, NodeType::AssetServer);

    auto nodeList = DependencyManager::get<NodeList>();
    nodeList->addNodeTypeToInterestSet(NodeType::Agent);

    const QString RESOURCES_PATH = "assets";

    _resourcesDirectory = QDir(ServerPathUtils::getDataDirectory()).filePath(RESOURCES_PATH);

    qDebug() << "Creating resources directory";
    _resourcesDirectory.mkpath(".");

    bool noExistingAssets = !_resourcesDirectory.exists() \
        || _resourcesDirectory.entryList(QDir::Files).size() == 0;

    if (noExistingAssets) {
        qDebug() << "Asset resources directory not found, searching for existing asset resources";
        QString oldDataDirectory = QCoreApplication::applicationDirPath();
        auto oldResourcesDirectory = QDir(oldDataDirectory).filePath("resources/" + RESOURCES_PATH);


        if (QDir(oldResourcesDirectory).exists()) {
            qDebug() << "Existing assets found in " << oldResourcesDirectory << ", copying to " << _resourcesDirectory;


            QDir resourcesParentDirectory = _resourcesDirectory.filePath("..");
            if (!resourcesParentDirectory.exists()) {
                qDebug() << "Creating data directory " << resourcesParentDirectory.absolutePath();
                resourcesParentDirectory.mkpath(".");
            }

            auto files = QDir(oldResourcesDirectory).entryList(QDir::Files);

            for (auto& file : files) {
                auto from = oldResourcesDirectory + QDir::separator() + file;
                auto to = _resourcesDirectory.absoluteFilePath(file);
                qDebug() << "\tCopying from " << from << " to " << to;
                QFile::copy(from, to);
            }

        }
    }
    qDebug() << "Serving files from: " << _resourcesDirectory.path();

    // Scan for new files
    qDebug() << "Looking for new files in asset directory";
    auto files = _resourcesDirectory.entryInfoList(QDir::Files);
    QRegExp filenameRegex { "^[a-f0-9]{" + QString::number(SHA256_HASH_HEX_LENGTH) + "}(\\..+)?$" };
    for (const auto& fileInfo : files) {
        auto filename = fileInfo.fileName();
        if (!filenameRegex.exactMatch(filename)) {
            qDebug() << "Found file: " << filename;
            if (!fileInfo.isReadable()) {
                qDebug() << "\tCan't open file for reading: " << filename;
                continue;
            }

            // Read file
            QFile file { fileInfo.absoluteFilePath() };
            file.open(QFile::ReadOnly);
            QByteArray data = file.readAll();

            auto hash = hashData(data);
            auto hexHash = hash.toHex();

            qDebug() << "\tMoving " << filename << " to " << hexHash;

            file.rename(_resourcesDirectory.absoluteFilePath(hexHash) + "." + fileInfo.suffix());
        }
    }
}