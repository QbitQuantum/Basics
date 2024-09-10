bool SubversionBackend::AppendText(const QString path, const QString text) {
    QString repoPath(path);
    QString fileName = QFileInfo(path).baseName();
    repoPath.replace(QRegExp("\\/[^\\/]+$"), "");
    QTemporaryFile tmpFile("changelogger");
    QString tmpPath;

    if (!tmpFile.open()) {
        return false;
    }
    tmpPath = tmpFile.fileName();
    tmpFile.remove();
    QDir(QDir::tempPath()).mkdir(tmpPath);
    tmpPath.prepend(QDir::separator());
    tmpPath.prepend(QDir::tempPath());

    if (QProcess::execute("svn", QStringList() << "co" << "--depth" << "files" << repoPath << tmpPath) != 0) {
        qDebug() << "Fehler beim auschecken nach: " << tmpPath;
        SubversionBackend::RecursiveRemove(tmpPath);
        return false;
    }

    qDebug() << "Checkout liegt in: " << tmpPath;
    qDebug() << "Filename ist: " << fileName;

    QString localChangeLogPath = tmpPath + QDir::separator() + fileName;
    QFile file(localChangeLogPath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << localChangeLogPath + " kann nicht zum lesen geöffnet werden!";
        SubversionBackend::RecursiveRemove(tmpPath);
        return false;
    }
    QString oldContent = QString::fromUtf8(file.readAll());
    file.close();

    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << localChangeLogPath + " kann nicht zum schreiben geöffnet werden!";
        SubversionBackend::RecursiveRemove(tmpPath);
        return false;
    }
    file.write(text.trimmed().toUtf8());
    file.write("\n\n");
    file.write(oldContent.trimmed().toUtf8());
    file.write("\n");
    file.close();

    qDebug() << localChangeLogPath + " geschrieben!";

    if (QProcess::execute("svn", QStringList() << "ci" << localChangeLogPath << "-m" << "Update via ChangeLogger") != 0) {
        qDebug() << "Fehler beim Check-In: " + tmpPath;
        return false;
    }

    SubversionBackend::RecursiveRemove(tmpPath);

    return true;
}