bool SynchronousProcess::stopProcess(QProcess &p)
{
    if (p.state() != QProcess::Running)
        return true;
    p.terminate();
    if (p.waitForFinished(300))
        return true;
    p.kill();
    return p.waitForFinished(300);
}