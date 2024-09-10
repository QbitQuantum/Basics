void FlashPlayerActiveX::build(NSIS *installer, Version version)
{
    Q_UNUSED(version);

    isError = false;
    download(version);
    if (!isError) {
        installer->build(
                    objectName(),
                    getOutputFile(),
                    NSIS::Zlib,
                    40,
                    QStringList(),
                    tempFiles,
                    loadResource(":NSIS/FlashPlayerActiveX/main.nsh").replace(
                        "${Installer}",
                        QFileInfo(tempFiles.first()).fileName())
                    );
    }
    cleanup();
}