//0 - exit on finish, 1 - exit on cancel
TCmdButton waitForFinishPlayOrCancel(QProcess *videoPlayer)
{
    //extern QProcess videoPlayer;
    extern CommandController cmdCtl;

    QEventLoop el;

    QMetaObject::Connection m_conn1, m_conn2;

    m_conn1 = QObject::connect(&cmdCtl, &CommandController::buttonCancel, [&el]() { el.exit(cmdButtonCancel); });
    //QObject::connect((QObject*)&videoPlayer, &QProcess::finished, [&el]() { el.exit(0); });
    m_conn2 = QObject::connect(videoPlayer, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
          [&el](int exitCode, QProcess::ExitStatus exitStatus){ qDebug() <<"video finished signal exit code " << exitCode; el.exit(cmdFinished); });

    TCmdButton ret = (TCmdButton)el.exec();

    QObject::disconnect(m_conn1);
    QObject::disconnect(m_conn2);

    return ret;
}