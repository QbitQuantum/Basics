void BootloaderInstallHex::installStage2(void)
{
    emit logItem(tr("Adding bootloader to firmware file"), LOGINFO);
    QCoreApplication::processEvents();

    // local temp file
    QTemporaryFile tempbin;
    tempbin.open();
    QString tempbinName = tempbin.fileName();
    tempbin.close();
    // get temporary files filenames -- external tools need this.
    m_descrambled.open();
    QString descrambledName = m_descrambled.fileName();
    m_descrambled.close();
    m_tempfile.open();
    QString tempfileName = m_tempfile.fileName();
    m_tempfile.close();

    int origin = 0;
    switch(m_model) {
        case 3:
            origin = 0x3f0000;
            break;
        case 2:
        case 1:
            origin = 0x1f0000;
            break;
        default:
            origin = 0;
            break;
    }

    // iriver decode already done in stage 1
    int result;
    if((result = mkboot_iriver(descrambledName.toLocal8Bit().constData(),
                    tempfileName.toLocal8Bit().constData(),
                    tempbinName.toLocal8Bit().constData(), origin)) < 0)
    {
        QString error;
        switch(result) {
            case -1: error = tr("could not open input file"); break;
            case -2: error = tr("reading header failed"); break;
            case -3: error = tr("reading firmware failed"); break;
            case -4: error = tr("can't open bootloader file"); break;
            case -5: error = tr("reading bootloader file failed"); break;
            case -6: error = tr("can't open output file"); break;
            case -7: error = tr("writing output file failed"); break;
        }
        emit logItem(tr("Error in patching: %1").arg(error), LOGERROR);

        emit done(true);
        return;
    }
    QTemporaryFile targethex;
    targethex.open();
    QString targethexName = targethex.fileName();
    if((result = iriver_encode(tempbinName.toLocal8Bit().constData(),
                    targethexName.toLocal8Bit().constData(), FALSE)) < 0)
    {
        emit logItem(tr("Error in scramble: %1").arg(scrambleError(result)), LOGERROR);
        targethex.close();

        emit done(true);
        return;
    }

    // finally check the md5sum of the created file
    QByteArray filedata;
    filedata = targethex.readAll();
    targethex.close();
    QString hash = QCryptographicHash::hash(filedata,
            QCryptographicHash::Md5).toHex();
    qDebug() << "[BootloaderInstallHex] created hexfile hash:" << hash;

    emit logItem(tr("Checking modified firmware file"), LOGINFO);
    if(hash != QString(md5sums[m_hashindex].patched)) {
        emit logItem(tr("Error: modified file checksum wrong"), LOGERROR);
        targethex.remove();
        emit done(true);
        return;
    }
    // finally copy file to player
    targethex.copy(m_blfile);

    emit logItem(tr("Success: modified firmware file created"), LOGINFO);
    logInstall(LogAdd);
    emit done(false);

    return;
}