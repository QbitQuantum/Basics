void Dynamic::stop(bool sendClear)
{
    if (isRemote()) {
        if (sendClear) {
            sendCommand(Control, QStringList() << "stop" << "1");
        } else {
            sendCommand(Control, QStringList() << "stop");
        }
        return;
    }

    #if !defined Q_OS_WIN
    int i=currentEntry.isEmpty() ? -1 : entryList.indexOf(currentEntry);
    QModelIndex idx=index(i, 0, QModelIndex());
    int pid=getPid();

    if (!pid) {
        if (sendClear) {
            emit clear();
        }
        currentEntry=QString();
        emit running(false);
        if (idx.isValid()) {
            emit dataChanged(idx, idx);
        }
        return;
    }

    if (0!=::kill(pid, 0)) {
        if (sendClear) {
            emit clear();
        }
        currentEntry=QString();
        emit running(false);
        if (idx.isValid()) {
            emit dataChanged(idx, idx);
        }
        return;
    }

    if (controlApp(false)) {
        if (sendClear) {
            emit clear();
        }
        currentEntry=QString();
        emit running(isRunning());
        if (idx.isValid()) {
            emit dataChanged(idx, idx);
        }
        return;
    }
    #endif
}