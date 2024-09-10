void CManageFileTransfer::slotFileReceived(const QString& szId, QSharedPointer<CFileTransfer> file)
{
    bool check = connect(file.data(), SIGNAL(sigFinished(const QString&, const QString&)),
                         SLOT(slotFinished(const QString&, const QString&)));
    Q_ASSERT(check);
    m_FileTransfer.insertMulti(szId, file);
    QSharedPointer<CUser> roster = GLOBAL_USER->GetUserInfoRoster(szId);
    if(roster.isNull())
    {
        LOG_MODEL_ERROR("CManageFileTransfer", "There isn't roster:%s", szId.toStdString().c_str());
        return;
    }

    if(CTool::isImageFile(file->GetFile()))
    {
        Accept(file);
    }
    QSharedPointer<CFileTransferAction> action(new CFileTransferAction(file, szId, QTime::currentTime(), false));
    roster->GetMessage()->AddMessage(action);
    GET_MAINWINDOW->ShowTrayIconMessage(roster->GetInfo()->GetShowName() + ":", tr("Send file %1").arg(file->GetFile()));
    emit GET_CLIENT->sigMessageUpdate(szId);
}