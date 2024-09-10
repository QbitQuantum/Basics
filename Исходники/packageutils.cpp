bool PackageUtils::prepareWidget()
{
    QString widgetInstallPath(m_packageRootPath + m_installationPath);
    while (widgetInstallPath.endsWith(QDir::separator()))
        widgetInstallPath.chop(1);

    QDir dir;
    if (!dir.mkpath(widgetInstallPath.left(widgetInstallPath.lastIndexOf(QDir::separator()))))
        return false;

#if defined(Q_OS_MAEMO5)
    // dpkg on M5 doesn't support long path name, thus unzip the .wgt in postinst script
    m_installedSize += QFileInfo(m_widget->widgetBundlePath()).size();
    if (!dir.mkpath(widgetInstallPath)
        || !QFile::copy(m_widget->widgetBundlePath(), widgetInstallPath + QDir::separator() + QFileInfo(m_widget->widgetBundlePath()).fileName()))
        return false;
#else
    // move the unzipped widget to the temp folder
    m_installedSize += Zzip::uncompressedSize(m_widget->widgetBundlePath());
    if (!dir.rename(m_sourcePath, widgetInstallPath + QDir::separator()))
        return false;

    QDir baseRootDir(m_packageRootPath);
    baseRootDir.mkpath("etc/secure/s/" + m_packageName);
    baseRootDir.mkpath(m_properties->resourcePath());
#endif

#ifdef Q_OS_MAEMO6
    // keep the original .wgt for backup
    m_installedSize += QFileInfo(m_widget->widgetBundlePath()).size();
    QString wgtFilePath(m_packageRootPath + BACKUP_SCRIPTS_DIR + "/install/");
    if (!dir.mkpath(wgtFilePath) || !QFile::copy(m_widget->widgetBundlePath(), wgtFilePath + m_appId + ".wgt"))
        return false;
#endif

    return true;
}