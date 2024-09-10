bool DatabaseTabWidget::saveDatabaseAs(Database* db)
{
    DatabaseManagerStruct& dbStruct = m_dbList[db];
    QString oldFileName;
    if (dbStruct.saveToFilename) {
        oldFileName = dbStruct.filePath;
    }
    else {
        oldFileName = tr("New database").append(".kdbx");
    }
    QString fileName = fileDialog()->getSaveFileName(this, tr("Save database as"),
                                                     oldFileName, tr("KeePass 2 Database").append(" (*.kdbx)"),
                                                     nullptr, 0, "kdbx");
    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString lockFilePath;
        if (fileInfo.exists()) {
            // returns empty string when file doesn't exist
            lockFilePath = fileInfo.canonicalPath();
        }
        else {
            lockFilePath = fileInfo.absolutePath();
        }
        QString lockFileName = QString("%1/.%2.lock").arg(lockFilePath, fileInfo.fileName());
        QScopedPointer<QLockFile> lockFile(new QLockFile(lockFileName));
        lockFile->setStaleLockTime(0);
        if (!lockFile->tryLock()) {
            // for now silently ignore if we can't create a lock file
            // due to lack of permissions
            if (lockFile->error() != QLockFile::PermissionError) {
                QMessageBox::StandardButton result = MessageBox::question(this, tr("Save database as"),
                    tr("The database you are trying to save as is locked by another instance of KeePassX.\n"
                       "Do you want to save it anyway?"),
                    QMessageBox::Yes | QMessageBox::No);

                if (result == QMessageBox::No) {
                    return false;
                }
                else {
                    // take over the lock file if possible
                    if (lockFile->removeStaleLockFile()) {
                        lockFile->tryLock();
                    }
                }
            }
        }

        QSaveFile saveFile(fileName);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            MessageBox::critical(this, tr("Error"), tr("Writing the database failed.") + "\n\n"
                                 + saveFile.errorString());
            return false;
        }

        m_writer.writeDatabase(&saveFile, db);
        if (m_writer.hasError()) {
            MessageBox::critical(this, tr("Error"), tr("Writing the database failed.") + "\n\n"
                                 + m_writer.errorString());
            return false;
        }
        if (!saveFile.commit()) {
            MessageBox::critical(this, tr("Error"), tr("Writing the database failed.") + "\n\n"
                                 + saveFile.errorString());
            return false;
        }

        dbStruct.modified = false;
        dbStruct.saveToFilename = true;
        dbStruct.readOnly = false;
        dbStruct.filePath = fileInfo.absoluteFilePath();
        dbStruct.canonicalFilePath = fileInfo.canonicalFilePath();
        dbStruct.fileName = fileInfo.fileName();
        dbStruct.dbWidget->updateFilename(dbStruct.filePath);
        delete dbStruct.lockFile;
        dbStruct.lockFile = lockFile.take();
        updateTabName(db);
        updateLastDatabases(dbStruct.filePath);
        return true;
    }
    else {
        return false;
    }
}