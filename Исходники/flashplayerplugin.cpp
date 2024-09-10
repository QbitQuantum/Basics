void FlashPlayerPlugin::build(NSIS *installer, Version version)
{
    Q_UNUSED(version);

    isError = false;
    download();
    if (!isError) {
        QStringList blockingProcesses(browsers());
        blockingProcesses.removeAll("chrome.exe");
        isError = !installer->build(
                    objectName(),
                    getOutputFile(),
                    NSIS::Zlib,
                    40,
                    blockingProcesses,
                    tempFiles,
                    loadResource(":NSIS/FlashPlayerPlugin/main.nsh")
                    );
    }
    cleanup();
}