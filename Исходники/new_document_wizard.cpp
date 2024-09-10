void NewDocumentWizard::accept()
// ----------------------------------------------------------------------------
//   Copy template into user's document folder
// ----------------------------------------------------------------------------
{
    QString docName = field("docName").toString();
    QString docLocation = field("docLocation").toString();
    QString dstPath = docLocation + "/" + docName;

    QDir dst(dstPath);
    if (dst.exists())
    {
        QString dstPathNative = QDir::toNativeSeparators(dstPath);
        int r = QMessageBox::warning(this, tr("Folder exists"),
                    tr("Document folder:\n%1\nalready exists. "
                       "Do you want to use it anyway (current content "
                       "will be deleted)?\n"
                       "Click No to choose another location.")
                       .arg(dstPathNative),
                       QMessageBox::Yes | QMessageBox::No);
        if (r != QMessageBox::Yes)
            return;
    }

    Template t = templates.at(field("templateIdx").toInt());

    bool ok = t.copyTo(dst);
    if (!ok)
    {
        QMessageBox::warning(this, tr("Error"),
                             tr("Failed to copy document template."));
        return;
    }

    docPath = dstPath;
    if (t.mainFile != "")
    {
        QString oldName = t.mainFile.replace(QRegExp("\\.ddd$"), "");
        QString newName = docName;
        if (oldName != newName)
        {
            // Rename template main file to doc name.
            // We need to remove the destination file if it is there
            QDir dstDir = QDir(dstPath);
            Rename(dstDir, oldName, newName, ".ddd");
            Rename(dstDir, oldName, newName, ".ddd.sig");
            Rename(dstDir, oldName, newName, ".json");
            docPath = dstDir.filePath(newName + ".ddd");
        }
    }

#if !defined(CFG_NOGIT)
    // Create project to avoid prompt when document is first opened
    RepositoryFactory::repository(dstPath, RepositoryFactory::Create);
#endif
    QDialog::accept();
}