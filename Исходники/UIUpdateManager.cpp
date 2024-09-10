void UIUpdateManager::checkIfUpdateIsNecessaryForExtensionPack(bool /* fForceCall */)
{
    /* Check if updater instance already created: */
    if (UIDownloaderExtensionPack::current())
        return;

    /* Get extension pack information: */
    CExtPack extPack = vboxGlobal().virtualBox().GetExtensionPackManager().Find(UI_ExtPackName);
    /* Check if extension pack is really installed: */
    if (extPack.isNull())
        return;

    /* Get VirtualBox version: */
    VBoxVersion vboxVersion(vboxGlobal().vboxVersionStringNormalized());
    /* Get extension pack version: */
    QString strExtPackVersion(extPack.GetVersion().remove(VBOX_BUILD_PUBLISHER));
    VBoxVersion extPackVersion(strExtPackVersion);
    /* Check if extension pack version less than required: */
    if ((vboxVersion.z() % 2 != 0) /* Skip unstable VBox version */ ||
        !(extPackVersion < vboxVersion) /* Ext Pack version more or equal to VBox version */)
        return;

    /* Ask the user about extension pack downloading: */
    if (!msgCenter().proposeDownloadExtensionPack(UI_ExtPackName, strExtPackVersion))
        return;

    /* Run downloader for VirtualBox extension pack: */
    UIDownloaderExtensionPack::download(this);
}