void QuaMainWindow::on_mIBFTreeView_selectionChanged_triggered(const QModelIndex & current, const QModelIndex & previous)
{
    if ( mQuaTextEdit->document()->isModified() )
    {
        mQuaTextEdit->IBFSaveToFile(mQuaTextEdit->windowFilePath());
    }

    if ( !mIBFFileSystemModel->fileInfo(current).isFile() )
    {
        const bool wasBlocked = mQuaTextEdit->blockSignals(true);

        mQuaTextEdit->clear();
        mQuaTextEdit->setEnabled(false);

        mQuaTextEdit->blockSignals(wasBlocked);

        return;
    }

    QString tFileName = mIBFFileSystemModel->fileInfo(current).absoluteFilePath();

    if ( tFileName.isEmpty() )
    {
        return;
    }

    if ( !QFile::exists(tFileName) )
    {
        return;
    }

    QFile tFile(tFileName);

    if ( !tFile.open(QFile::ReadOnly) )
    {
        return;
    }

    QByteArray tByteArray = tFile.readAll();
    QTextCodec * tTextCodec = Qt::codecForHtml(tByteArray);

    QString tString = tTextCodec->toUnicode(tByteArray);

    const bool wasBlocked = mQuaTextEdit->blockSignals(true);

    if ( Qt::mightBeRichText(tString) )
    {
        mQuaTextEdit->setHtml(tString);
    }
    else
    {
        tString = QString::fromLocal8Bit(tByteArray);
        mQuaTextEdit->setPlainText(tString);
    }

    mQuaTextEdit->blockSignals(wasBlocked);

    mQuaTextEdit->setWindowFilePath(tFileName);
    mQuaTextEdit->setEnabled(true);

}