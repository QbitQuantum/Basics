void CleanDialog::setFileList(const QString &workingDirectory, const QStringList &l)
{
    d->m_workingDirectory = workingDirectory;
    d->ui.groupBox->setTitle(tr("Repository: %1").
                             arg(QDir::toNativeSeparators(workingDirectory)));
    if (const int oldRowCount = d->m_filesModel->rowCount())
        d->m_filesModel->removeRows(0, oldRowCount);

    QStyle *style = QApplication::style();
    const QIcon folderIcon = style->standardIcon(QStyle::SP_DirIcon);
    const QIcon fileIcon = style->standardIcon(QStyle::SP_FileIcon);
    const QString diffSuffix = QLatin1String(".diff");
    const QString patchSuffix = QLatin1String(".patch");
    const QString proUserSuffix = QLatin1String(".pro.user");
    const QString qmlProUserSuffix = QLatin1String(".qmlproject.user");
    const QChar slash = QLatin1Char('/');
    // Do not initially check patches or 'pro.user' files for deletion.
    foreach(const QString &fileName, l) {
        const QFileInfo fi(workingDirectory + slash + fileName);
        const bool isDir = fi.isDir();
        QStandardItem *nameItem = new QStandardItem(QDir::toNativeSeparators(fileName));
        nameItem->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        nameItem->setIcon(isDir ? folderIcon : fileIcon);
        const bool saveFile = !isDir && (fileName.endsWith(diffSuffix)
                                        || fileName.endsWith(patchSuffix)
                                        || fileName.endsWith(proUserSuffix)
                                        || fileName.endsWith(qmlProUserSuffix));
        nameItem->setCheckable(true);
        nameItem->setCheckState(saveFile ? Qt::Unchecked : Qt::Checked);
        nameItem->setData(QVariant(fi.absoluteFilePath()), fileNameRole);
        nameItem->setData(QVariant(isDir), isDirectoryRole);
        // Tooltip with size information
        if (fi.isFile()) {
            const QString lastModified = fi.lastModified().toString(Qt::DefaultLocaleShortDate);
            nameItem->setToolTip(tr("%1 bytes, last modified %2")
                                 .arg(fi.size()).arg(lastModified));
        }
        d->m_filesModel->appendRow(nameItem);
    }

    for (int c = 0; c < d->m_filesModel->columnCount(); c++)
        d->ui.filesTreeView->resizeColumnToContents(c);
}