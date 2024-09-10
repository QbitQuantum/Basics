/**
 * @brief moves all movies in given path to seperate directories
 * @param path place to organize
 */
void MovieFilesOrganizer::moveToDirs(QString path)
{
    path = QDir::toNativeSeparators(path);
    QFileInfo fi(path);
    if (!fi.isDir()) {
        canceled(tr("Source %1 is no directory").arg(path));
    }

    QList<QStringList> contents;
    MovieFileSearcher *fileSearcher = new MovieFileSearcher(this);
    fileSearcher->scanDir(path, contents, false, true);
    fileSearcher->deleteLater();

    int pos = path.lastIndexOf(QDir::separator());
    QString dirName = path.right(path.length() - pos -1);
    QString fileName;
    NameFormatter *nameFormat = NameFormatter::instance(this);


    foreach (QStringList movie, contents) {
        int pos = movie.at(0).lastIndexOf(QDir::separator());
        if (!(movie.at(0).left(pos).endsWith(dirName))) {
            qDebug() << "skipping " << movie.at(0);
            continue;
        }

        fi.setFile(movie.at(0));
        fileName = fi.completeBaseName();
        QDir *dir = new QDir();

        QString newFolder;
        if (movie.length() == 1)
            newFolder = path + QDir::separator() + nameFormat->formatName(fileName);
        else if (movie.length() > 1)
            newFolder = path + QDir::separator() + nameFormat->formatName(
                        nameFormat->formatParts(fileName));
        else
            continue;

        if (!(dir->mkdir(newFolder)))
            continue;

        foreach (QString file, movie) {
            if (!dir->rename(file, newFolder +
                             QDir::separator() +
                             file.right(file.length() -
                                        file.lastIndexOf
                                        (QDir::separator()) - 1)))
                qDebug() << "Moving " << file << "to " << newFolder << " failed.";
        }
    }