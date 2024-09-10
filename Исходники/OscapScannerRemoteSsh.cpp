void OscapScannerRemoteSsh::evaluate()
{
    if (mDryRun)
    {
        signalCompletion(mCancelRequested);
        return;
    }

    ensureConnected();

    if (mCancelRequested)
    {
        signalCompletion(true);
        return;
    }

    emit infoMessage(QObject::tr("Querying capabilities on remote machine..."));

    {
        SshSyncProcess proc(mSshConnection, this);
        proc.setCommand(SCAP_WORKBENCH_REMOTE_OSCAP_PATH);
        proc.setArguments(QStringList("--v"));
        proc.setCancelRequestSource(&mCancelRequested);
        proc.run();

        if (proc.getExitCode() != 0)
        {
            emit errorMessage(
                QObject::tr("Failed to query capabilities of oscap on local machine.\n"
                        "Diagnostic info:\n%1").arg(proc.getDiagnosticInfo())
            );

            mCancelRequested = true;
            signalCompletion(mCancelRequested);
            return;
        }

        mCapabilities.parse(proc.getStdOutContents());
    }

    if (!checkPrerequisites())
    {
        mCancelRequested = true;
        signalCompletion(mCancelRequested);
        return;
    }

    QStringList baseArgs;
    baseArgs.append("-o"); baseArgs.append(QString("ControlPath=%1").arg(mSshConnection._getMasterSocket()));
    baseArgs.append(mTarget);

    QString diagnosticInfo;

    emit infoMessage(QObject::tr("Copying input data to remote target..."));

    const QString inputFile = copyInputFileOver();
    const QString tailoringFile = mSession->hasTailoring() ?
        copyFileOver(mSession->getTailoringFilePath()) : QString();

    if (mCancelRequested)
    {
        signalCompletion(true);
        return;
    }

    const QString reportFile = createRemoteTemporaryFile();
    const QString resultFile = createRemoteTemporaryFile();
    const QString arfFile = createRemoteTemporaryFile();
    const QString workingDir = createRemoteTemporaryDirectory();

    // TODO: We could be leaking any of the temporary files at this point!
    if (mCancelRequested)
    {
        signalCompletion(true);
        return;
    }

    QStringList args;

    if (mScannerMode == SM_OFFLINE_REMEDIATION)
    {
        args = buildOfflineRemediationArgs(inputFile,
                resultFile,
                reportFile,
                arfFile);
    }
    else
    {
        args = buildEvaluationArgs(inputFile,
                tailoringFile,
                resultFile,
                reportFile,
                arfFile,
                mScannerMode == SM_SCAN_ONLINE_REMEDIATION);
    }

    const QString sshCmd = args.join(" ");

    emit infoMessage(QObject::tr("Starting the remote process..."));

    QProcess process(this);

    process.start(SCAP_WORKBENCH_LOCAL_SSH_PATH, baseArgs + QStringList(QString("cd '%1'; " SCAP_WORKBENCH_REMOTE_OSCAP_PATH " %2").arg(workingDir).arg(sshCmd)));
    process.waitForStarted();

    if (process.state() != QProcess::Running)
    {
        emit errorMessage(QObject::tr("Failed to start ssh. Perhaps the executable was not found?"));
        mCancelRequested = true;
    }

    const unsigned int pollInterval = 100;

    emit infoMessage(QObject::tr("Processing on the remote machine..."));
    while (!process.waitForFinished(pollInterval))
    {
        // read everything new
        readStdOut(process);
        watchStdErr(process);

        // pump the event queue, mainly because the user might want to cancel
        QAbstractEventDispatcher::instance(mScanThread)->processEvents(QEventLoop::AllEvents);

        if (mCancelRequested)
        {
            emit infoMessage(QObject::tr("Cancellation was requested! Terminating..."));
            // TODO: On Windows we have to kill immediately, terminate() posts WM_CLOSE
            //       but oscap doesn't have any event loop running.
            process.terminate();
            break;
        }
    }

    if (mCancelRequested)
    {
        unsigned int waited = 0;
        while (!process.waitForFinished(pollInterval))
        {
            waited += pollInterval;
            if (waited > 10000) // 10 seconds should be enough for the process to terminate
            {
                emit warningMessage(QObject::tr("The oscap process didn't terminate in time, it will be killed instead."));
                // if it didn't terminate, we have to kill it at this point
                process.kill();
                break;
            }
        }
    }
    else
    {
        // read everything left over
        readStdOut(process);
        watchStdErr(process);

        mResults = readRemoteFile(resultFile, QObject::tr("XCCDF results")).toUtf8();
        mReport = readRemoteFile(reportFile, QObject::tr("XCCDF report (HTML)")).toUtf8();
        mARF = readRemoteFile(arfFile, QObject::tr("Result DataStream (ARF)")).toUtf8();
    }

    emit infoMessage(QObject::tr("Cleaning up..."));

    // Remove all the temporary remote files
    removeRemoteFile(inputFile, QObject::tr("input file"));
    if (!tailoringFile.isEmpty())
        removeRemoteFile(tailoringFile, QObject::tr("tailoring file"));
    removeRemoteFile(resultFile, QObject::tr("XCCDF result file"));
    removeRemoteFile(reportFile, QObject::tr("XCCDF report file"));
    removeRemoteFile(arfFile, QObject::tr("Result DataStream file"));
    removeRemoteDirectory(workingDir, QObject::tr("Temporary Working Directory"));

    emit infoMessage(QObject::tr("Processing has been finished!"));
    signalCompletion(mCancelRequested);
}