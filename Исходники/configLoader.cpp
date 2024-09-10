void ConfigLoader::loadIncludes(QDomDocument const &config, QFileInfo const &currentFile)
{
    QDomNodeList includes = config.elementsByTagName("include");
    for (unsigned i = 0; i < includes.length(); i++) {
        QDomElement includeElement = includes.at(i).toElement();
        QString includeName = includeElement.attribute("name");
        QFileInfo included = QFileInfo(currentFile.dir(), includeName);
        if (included.exists()) {
            load(included.canonicalFilePath());
        } else {
            fprintf(stderr, "Error 13 (%s:%d,%d) : Include '%s' is unknown.\n",
                    currentFile.fileName().toLatin1().constData(),
                    includeElement.lineNumber(),
                    includeElement.columnNumber(),
                    includeName.toLatin1().constData()
            );
        }

    }
}