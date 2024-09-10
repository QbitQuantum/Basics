bool OscapScannerBase::tryToReadStdOutChar(QProcess& process)
{
    char readChar = '\0';
    if (!process.getChar(&readChar))
        return false;

    if (!mCapabilities.progressReporting())
        return true; // We did read something but it's not in a format we can parse.

    if (readChar == ':')
    {
        switch (mReadingState)
        {
            case RS_READING_PREFIX:
                {
                    // Openscap <= 1.2.10 (60fb9f0c98eee) sends this message through stdout
                    if (mReadBuffer=="Downloading")
                    {
                         mReadingState = RS_READING_DOWNLOAD_FILE;
                    }
                    else
                    {
                        mLastRuleID = mReadBuffer;
                        emit progressReport(mLastRuleID, "processing");
                        mReadingState = RS_READING_RULE_RESULT;
                    }
                    mReadBuffer = "";
                }
                break;

            case RS_READING_RULE_RESULT:
                {
                    emit warningMessage(QString(
                                QObject::tr("Error when parsing scan progress output from stdout of the 'oscap' process. "
                                    "':' encountered while not reading rule ID, newline and/or rule result are missing! "
                                    "Read buffer is '%1'.")).arg(mReadBuffer));
                    mReadBuffer = "";
                }
                break;
            case RS_READING_DOWNLOAD_FILE:
                {
                    // When fetching remote content, openscap will inform scap-workbench about
                    // resources being downloaded. Keep any colon found in URL of file being downloaded.
                    mReadBuffer.append(QChar::fromAscii(readChar));
                }
                break;

            default:
                // noop
                break;
        }
    }
    else if (readChar == '\n')
    {
        switch(mReadingState)
        {
            case RS_READING_PREFIX:
                // If we found a '\n' while reading prefix, we might have received an error or
                // warning message through stdout.
                if (mReadBuffer.contains("--fetch-remote-resources"))
                {
                    // If message is about --fetch-remote-resources, emit a nice warning.
                    // This is needed for workbench to be able to handle messages from machines
                    // running older versions of openscap.
                    // From openscap version 1.2.11, this message is sent through stderr
                    // and therefore is handled accordingly by workbench.
                    emit warningMessage(guiFriendlyMessage(mReadBuffer));
                }
                else
                {
                    // No other error or warning messages are expected through stdout,
                    // so it is likely that a parsing error occured.
                    emit warningMessage(QString(
                                QObject::tr("Error when parsing scan progress output from stdout of the 'oscap' process. "
                                    "Newline encountered while reading rule ID, rule result and/or ':' are missing! "
                                    "Read buffer is '%1'.")).arg(mReadBuffer));
                }
                break;

            case RS_READING_RULE_RESULT:
                emit progressReport(mLastRuleID, mReadBuffer);
                break;

            case RS_READING_DOWNLOAD_FILE_STATUS:
                {
                    QString downloadStatus = mReadBuffer.mid(1);
                    if (downloadStatus == "ok")
                        emit infoMessage(QString("Downloading of \"%1\" finished: %2").arg(mLastDownloadingFile).arg(downloadStatus));
                    else
                        emit warningMessage(QString("Failed to download \"%1\"!").arg(mLastDownloadingFile));
                }
                break;
            default:
                // noop
                break;
        }
        mReadingState = RS_READING_PREFIX;
        mReadBuffer = "";
    }
    else if ( (readChar == '.') && (mReadingState == RS_READING_DOWNLOAD_FILE) && (mReadBuffer.endsWith(" ..")))
    {
        int urlLen = mReadBuffer.length();
        urlLen -= 1; // without first space
        urlLen -= 3; // without "progress dots"
        mLastDownloadingFile = mReadBuffer.mid(1, urlLen);

        emit infoMessage(QString("Downloading of \"%1\"...").arg(mLastDownloadingFile));

        mReadBuffer = "";
        mReadingState = RS_READING_DOWNLOAD_FILE_STATUS;
    }
    else
    {
        // we know for sure that buffer[0] can only contain ASCII characters
        // (IDs and special keywords regarding rule status)
        mReadBuffer.append(QChar::fromAscii(readChar));
    }

    return true;
}