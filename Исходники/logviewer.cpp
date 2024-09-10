void LogViewer::cancelClicked(void)
{
    QString tempDir = gCoreContext->GetSetting("MythArchiveTempDir", "");
    QFile lockFile(tempDir + "/logs/mythburncancel.lck");

    if (!lockFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        LOG(VB_GENERAL, LOG_ERR,
            "LogViewer: Failed to create mythburncancel.lck file");

    lockFile.write("Cancel\n\r");
    lockFile.close();

    ShowOkPopup(tr("Background creation has been asked to stop.\n" 
                   "This may take a few minutes."));
}