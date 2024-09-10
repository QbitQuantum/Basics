/**
 * Attempt the actual installation.
 *
 * This code is shared by UIGlobalSettingsExtension::sltInstallPackage and UISelectorWindow::sltOpenUrls.
 *
 * @param   strFilePath     The path to the tarball.
 * @param   strDigest       The digest of the file (SHA-256). Empty string if no
 *                          digest was performed.
 * @param   pParent         The parent widget.
 * @param   pstrExtPackName Where to return the extension pack name. Optional.
 */
/*static*/ void UIGlobalSettingsExtension::doInstallation(QString const &strFilePath, QString const &strDigest,
                                                          QWidget *pParent, QString *pstrExtPackName)
{
    /*
     * Open the extpack tarball via IExtPackManager.
     */
    CExtPackManager manager = vboxGlobal().virtualBox().GetExtensionPackManager();
    CExtPackFile extPackFile;
    if (strDigest.isEmpty())
        extPackFile = manager.OpenExtPackFile(strFilePath);
    else
    {
        QString strFileAndHash = QString("%1::SHA-256=%2").arg(strFilePath).arg(strDigest);
        extPackFile = manager.OpenExtPackFile(strFileAndHash);
    }
    if (!manager.isOk())
    {
        msgCenter().cannotOpenExtPack(strFilePath, manager, pParent);
        return;
    }

    if (!extPackFile.GetUsable())
    {
        msgCenter().badExtPackFile(strFilePath, extPackFile, pParent);
        return;
    }

    QString strPackName = extPackFile.GetName();
    QString strPackDescription = extPackFile.GetDescription();
    QString strPackVersion = QString("%1r%2%3").arg(extPackFile.GetVersion()).arg(extPackFile.GetRevision()).arg(extPackFile.GetEdition());

    /*
     * Check if there is a version of the extension pack already
     * installed on the system and let the user decide what to do about
     * it.
     */
    CExtPack extPackCur = manager.Find(strPackName);
    bool fReplaceIt = extPackCur.isOk();
    if (fReplaceIt)
    {
        QString strPackVersionCur = QString("%1r%2%3").arg(extPackCur.GetVersion()).arg(extPackCur.GetRevision()).arg(extPackCur.GetEdition());
        if (!msgCenter().confirmReplacePackage(strPackName, strPackVersion, strPackVersionCur, strPackDescription, pParent))
            return;
    }
    /*
     * If it's a new package just ask for general confirmation.
     */
    else
    {
        if (!msgCenter().confirmInstallingPackage(strPackName, strPackVersion, strPackDescription, pParent))
            return;
    }

    /*
     * Display the license dialog if required by the extension pack.
     */
    if (extPackFile.GetShowLicense())
    {
        QString strLicense = extPackFile.GetLicense();
        VBoxLicenseViewer licenseViewer(pParent);
        if (licenseViewer.showLicenseFromString(strLicense) != QDialog::Accepted)
            return;
    }

    /*
     * Install the selected package.
     *
     * Set the package name return value before doing this as the caller should
     * do a refresh even on failure.
     */
    QString displayInfo;
#ifdef RT_OS_WINDOWS
    if (pParent)
        displayInfo.sprintf("hwnd=%#llx", (uint64_t)(uintptr_t)pParent->winId());
#endif
    CProgress progress = extPackFile.Install(fReplaceIt, displayInfo);
    if (extPackFile.isOk())
    {
        if (progress.isNull())
            msgCenter().notifyAboutExtPackInstalled(strPackName, pParent);
        else
        {
            msgCenter().showModalProgressDialog(progress, tr("Extensions"));
            if (!progress.GetCanceled())
            {
                if (progress.isOk() && progress.GetResultCode() == 0)
                    msgCenter().notifyAboutExtPackInstalled(strPackName, pParent);
                else
                    msgCenter().cannotInstallExtPack(strFilePath, extPackFile, progress, pParent);
            }
        }
    }
    else
        msgCenter().cannotInstallExtPack(strFilePath, extPackFile, progress, pParent);

    if (pstrExtPackName)
        *pstrExtPackName = strPackName;
}