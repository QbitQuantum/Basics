void ProcessSocket::close()
{
    QProcess *proc = qobject_cast<QProcess *>(d);
    Q_ASSERT(proc);
    // Be nice to it, let it die peacefully before using an axe
    // QTBUG-5990, don't call waitForFinished() on a process which hadn't started
    if (proc->state() == QProcess::Running) {
        proc->terminate();
        proc->waitForFinished(200);
        proc->kill();
    }
}