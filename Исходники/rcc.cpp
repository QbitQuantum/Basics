bool RCCResourceLibrary::interpretResourceFile(QIODevice *inputDevice,
    const QString &fname, QString currentPath, bool ignoreErrors)
{
    Q_ASSERT(m_errorDevice);
    const QChar slash = QLatin1Char('/');
    if (!currentPath.isEmpty() && !currentPath.endsWith(slash))
        currentPath += slash;

    QDomDocument document;
    {
        QString errorMsg;
        int errorLine = 0;
        int errorColumn = 0;
        if (!document.setContent(inputDevice, &errorMsg, &errorLine, &errorColumn)) {
            if (ignoreErrors)
                return true;
            const QString msg = QString::fromUtf8("RCC Parse Error: '%1' Line: %2 Column: %3 [%4]\n").arg(fname).arg(errorLine).arg(errorColumn).arg(errorMsg);
            m_errorDevice->write(msg.toUtf8());
            return false;
        }
    }

    QDomElement domRoot = document.firstChildElement(m_strings.TAG_RCC).toElement();
    if (!domRoot.isNull() && domRoot.tagName() == m_strings.TAG_RCC) {
        for (QDomNode node = domRoot.firstChild(); !node.isNull(); node = node.nextSibling()) {
            if (!node.isElement())
                continue;

            QDomElement child = node.toElement();
            if (!child.isNull() && child.tagName() == m_strings.TAG_RESOURCE) {
                QLocale::Language language = QLocale::c().language();
                QLocale::Country country = QLocale::c().country();

                if (child.hasAttribute(m_strings.ATTRIBUTE_LANG)) {
                    QString attribute = child.attribute(m_strings.ATTRIBUTE_LANG);
                    QLocale lang = QLocale(attribute);
                    language = lang.language();
                    if (2 == attribute.length()) {
                        // Language only
                        country = QLocale::AnyCountry;
                    } else {
                        country = lang.country();
                    }
                }

                QString prefix;
                if (child.hasAttribute(m_strings.ATTRIBUTE_PREFIX))
                    prefix = child.attribute(m_strings.ATTRIBUTE_PREFIX);
                if (!prefix.startsWith(slash))
                    prefix.prepend(slash);
                if (!prefix.endsWith(slash))
                    prefix += slash;

                for (QDomNode res = child.firstChild(); !res.isNull(); res = res.nextSibling()) {
                    if (res.isElement() && res.toElement().tagName() == m_strings.TAG_FILE) {

                        QString fileName(res.firstChild().toText().data());
                        if (fileName.isEmpty()) {
                            const QString msg = QString::fromUtf8("RCC: Warning: Null node in XML of '%1'\n").arg(fname);
                            m_errorDevice->write(msg.toUtf8());
                        }
                        QString alias;
                        if (res.toElement().hasAttribute(m_strings.ATTRIBUTE_ALIAS))
                            alias = res.toElement().attribute(m_strings.ATTRIBUTE_ALIAS);
                        else
                            alias = fileName;

                        int compressLevel = m_compressLevel;
                        if (res.toElement().hasAttribute(m_strings.ATTRIBUTE_COMPRESS))
                            compressLevel = res.toElement().attribute(m_strings.ATTRIBUTE_COMPRESS).toInt();
                        int compressThreshold = m_compressThreshold;
                        if (res.toElement().hasAttribute(m_strings.ATTRIBUTE_THRESHOLD))
                            compressThreshold = res.toElement().attribute(m_strings.ATTRIBUTE_THRESHOLD).toInt();

                        // Special case for -no-compress. Overrides all other settings.
                        if (m_compressLevel == -2)
                            compressLevel = 0;

                        alias = QDir::cleanPath(alias);
                        while (alias.startsWith(QLatin1String("../")))
                            alias.remove(0, 3);
                        alias = QDir::cleanPath(m_resourceRoot) + prefix + alias;

                        QString absFileName = fileName;
                        if (QDir::isRelativePath(absFileName))
                            absFileName.prepend(currentPath);
                        QFileInfo file(absFileName);
                        if (!file.exists()) {
                            m_failedResources.push_back(absFileName);
                            const QString msg = QString::fromUtf8("RCC: Error in '%1': Cannot find file '%2'\n").arg(fname).arg(fileName);
                            m_errorDevice->write(msg.toUtf8());
                            if (ignoreErrors)
                                continue;
                            else
                                return false;
                        } else if (file.isFile()) {
                            const bool arc =
                                addFile(alias,
                                        RCCFileInfo(alias.section(slash, -1),
                                                    file,
                                                    language,
                                                    country,
                                                    RCCFileInfo::NoFlags,
                                                    compressLevel,
                                                    compressThreshold)
                                        );
                            if (!arc)
                                m_failedResources.push_back(absFileName);
                        } else {
                            QDir dir;
                            if (file.isDir()) {
                                dir.setPath(file.filePath());
                            } else {
                                dir.setPath(file.path());
                                dir.setNameFilters(QStringList(file.fileName()));
                                if (alias.endsWith(file.fileName()))
                                    alias = alias.left(alias.length()-file.fileName().length());
                            }
                            if (!alias.endsWith(slash))
                                alias += slash;
                            QDirIterator it(dir, QDirIterator::FollowSymlinks|QDirIterator::Subdirectories);
                            while (it.hasNext()) {
                                it.next();
                                QFileInfo child(it.fileInfo());
                                if (child.fileName() != QLatin1String(".") && child.fileName() != QLatin1String("..")) {
                                    const bool arc =
                                        addFile(alias + child.fileName(),
                                                RCCFileInfo(child.fileName(),
                                                            child,
                                                            language,
                                                            country,
                                                            RCCFileInfo::NoFlags,
                                                            compressLevel,
                                                            compressThreshold)
                                                );
                                    if (!arc)
                                        m_failedResources.push_back(child.fileName());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (m_root == 0) {
        const QString msg = QString::fromUtf8("RCC: Warning: No resources in '%1'.\n").arg(fname);
        m_errorDevice->write(msg.toUtf8());
        if (!ignoreErrors && m_format == Binary) {
            // create dummy entry, otherwise loading qith QResource will crash
            m_root = new RCCFileInfo(QString(), QFileInfo(),
                    QLocale::C, QLocale::AnyCountry, RCCFileInfo::Directory);
        }
    }

    return true;
}