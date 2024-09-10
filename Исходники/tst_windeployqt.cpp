static bool runProcess(const QString &binary,
                       const QStringList &arguments,
                       QString *errorMessage,
                       const QString &workingDir = QString(),
                       const QProcessEnvironment &env = QProcessEnvironment(),
                       int timeOut = 5000,
                       QByteArray *stdOut = Q_NULLPTR, QByteArray *stdErr = Q_NULLPTR)
{
    QProcess process;
    if (!env.isEmpty())
        process.setProcessEnvironment(env);
    if (!workingDir.isEmpty())
        process.setWorkingDirectory(workingDir);
    qDebug().noquote().nospace() << "Running: " << QDir::toNativeSeparators(binary)
        << ' ' << arguments.join(QLatin1Char(' '));
    process.start(binary, arguments, QIODevice::ReadOnly);
    if (!process.waitForStarted()) {
        *errorMessage = msgProcessError(process, "Failed to start");
        return false;
    }
    if (!process.waitForFinished(timeOut)) {
        *errorMessage = msgProcessError(process, "Timed out");
        process.terminate();
        if (!process.waitForFinished(300))
            process.kill();
        return false;
    }
    if (stdOut)
        *stdOut = process.readAllStandardOutput();
    if (stdErr)
        *stdErr= process.readAllStandardError();
    if (process.exitStatus() != QProcess::NormalExit) {
        *errorMessage = msgProcessError(process, "Crashed");
        return false;
    }
    if (process.exitCode() != QProcess::NormalExit) {
        *errorMessage = msgProcessError(process, "Exit code " + QString::number(process.exitCode()));
        return false;
    }
    return true;
}