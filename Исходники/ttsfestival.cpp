TTSStatus TTSFestival::voice(QString text, QString wavfile, QString* errStr)
{
    qDebug() << "[Festival] Voicing " << text << "->" << wavfile;

    QString path = RbSettings::subValue("festival-client",
            RbSettings::TtsPath).toString();
    QString cmd = QString("%1 --server localhost --otype riff --ttw --withlisp"
            " --output \"%2\" --prolog \"%3\" - ").arg(path).arg(wavfile).arg(prologPath);
    qDebug() << "[Festival] Client cmd: " << cmd;

    QProcess clientProcess;
    clientProcess.start(cmd);
    clientProcess.write(QString("%1.\n").arg(text).toAscii());
    clientProcess.waitForBytesWritten();
    clientProcess.closeWriteChannel();
    clientProcess.waitForReadyRead();
    QString response = clientProcess.readAll();
    response = response.trimmed();
    if(!response.contains("Utterance"))
    {
        qDebug() << "[Festival] Could not voice string: " << response;
        *errStr = tr("engine could not voice string");
        return Warning;
        /* do not stop the voicing process because of a single string
        TODO: needs proper settings */
    }
    clientProcess.closeReadChannel(QProcess::StandardError);
    clientProcess.closeReadChannel(QProcess::StandardOutput);
    clientProcess.terminate();
    clientProcess.kill();

    return NoError;
}