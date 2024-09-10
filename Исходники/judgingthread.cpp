void JudgingThread::runProgram()
{
    result = CorrectAnswer;
    int extraTime = qCeil(qMax(2000, timeLimit * 2) * extraTimeRatio);
    
#ifdef Q_OS_WIN32
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&sa, sizeof(sa));
    sa.bInheritHandle = TRUE;
    
    if (task->getStandardInputCheck())
        si.hStdInput = CreateFile((const WCHAR*)(inputFile.utf16()), GENERIC_READ,
                                  FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                                  OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (task->getStandardOutputCheck())
        si.hStdOutput = CreateFile((const WCHAR*)((workingDirectory + "_tmpout").utf16()), GENERIC_WRITE,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                                   CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    
    si.hStdError = CreateFile((const WCHAR*)((workingDirectory + "_tmperr").utf16()), GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, &sa,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    
    QString values = environment.toStringList().join('\0') + '\0';
    if (! CreateProcess(NULL, (WCHAR*)(QString("\"%1\" %2").arg(executableFile, arguments).utf16()), NULL, &sa,
                        TRUE, HIGH_PRIORITY_CLASS | CREATE_NO_WINDOW, (LPVOID)(values.toLocal8Bit().data()),
                        (const WCHAR*)(workingDirectory.utf16()), &si, &pi)) {
        if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
        if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
        CloseHandle(si.hStdError);
        score = 0;
        result = CannotStartProgram;
        return;
    }
    
    PROCESS_MEMORY_COUNTERS_EX info;
    ZeroMemory(&info, sizeof(info));
    info.cb = sizeof(info);
    if (memoryLimit != -1) {
        GetProcessMemoryInfo(pi.hProcess, (PROCESS_MEMORY_COUNTERS*)&info, sizeof(info));
        if (qMax(info.PrivateUsage, info.PeakWorkingSetSize) > memoryLimit * 1024 * 1024) {
            TerminateProcess(pi.hProcess, 0);
            if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
            if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
            CloseHandle(si.hStdError);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            score = 0;
            result = MemoryLimitExceeded;
            memoryUsed = timeUsed = -1;
            return;
        }
    }
    
	if (memoryLimit != -1)
        SetProcessWorkingSetSize(pi.hProcess, memoryLimit * 1024 * 1024 / 4, memoryLimit * 1024 * 1024);
    
    bool flag = false;
    QElapsedTimer timer;
    timer.start();
    
    while (timer.elapsed() <= timeLimit + extraTime) {
        if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
            flag = true;
            break;
        }
        if (memoryLimit != -1) {
            GetProcessMemoryInfo(pi.hProcess, (PROCESS_MEMORY_COUNTERS*)&info, sizeof(info));
            if (qMax(info.PrivateUsage, info.PeakWorkingSetSize) > memoryLimit * 1024 * 1024) {
                TerminateProcess(pi.hProcess, 0);
                if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
                if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
                CloseHandle(si.hStdError);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                score = 0;
                result = MemoryLimitExceeded;
                memoryUsed = timeUsed = -1;
                return;
            }
        }
        QCoreApplication::processEvents();
        if (stopJudging) {
            TerminateProcess(pi.hProcess, 0);
            if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
            if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
            CloseHandle(si.hStdError);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return;
        }
        Sleep(10);
    }
    
    if (! flag) {
        TerminateProcess(pi.hProcess, 0);
        if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
        if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
        CloseHandle(si.hStdError);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        score = 0;
        result = TimeLimitExceeded;
        timeUsed = -1;
        return;
    }
    
    unsigned long exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    if (exitCode != 0) {
        if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
        if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
        CloseHandle(si.hStdError);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        score = 0;
        result = RunTimeError;
        QFile file(workingDirectory + "_tmperr");
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            message = stream.readAll();
            file.close();
        }
        memoryUsed = timeUsed = -1;
        return;
    }
    
    FILETIME creationTime, exitTime, kernelTime, userTime;
    GetProcessTimes(pi.hProcess, &creationTime, &exitTime, &kernelTime, &userTime);
    
    SYSTEMTIME realTime;
    FileTimeToSystemTime(&userTime, &realTime);
    
    timeUsed = realTime.wMilliseconds
               + realTime.wSecond * 1000
               + realTime.wMinute * 60 * 1000
               + realTime.wHour * 60 * 60 * 1000;
    
    GetProcessMemoryInfo(pi.hProcess, (PROCESS_MEMORY_COUNTERS*)&info, sizeof(info));
    memoryUsed = info.PeakWorkingSetSize;
    
    if (task->getStandardInputCheck()) CloseHandle(si.hStdInput);
    if (task->getStandardOutputCheck()) CloseHandle(si.hStdOutput);
    CloseHandle(si.hStdError);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#endif
    
#ifdef Q_OS_LINUX
    QFile::copy(":/watcher/watcher_unix", workingDirectory + "watcher");
    QProcess::execute(QString("chmod +wx \"") + workingDirectory + "watcher" + "\"");
    
    QProcess *runner = new QProcess(this);
    QStringList argumentsList;
    argumentsList << QString("\"%1\" %2").arg(executableFile, arguments);
    if (task->getStandardInputCheck())
        argumentsList << QFileInfo(inputFile).absoluteFilePath();
    else
        argumentsList << "";
    if (task->getStandardOutputCheck())
        argumentsList << "_tmpout";
    else
        argumentsList << "";
    argumentsList << "_tmperr";
    argumentsList << QString("%1").arg(timeLimit + extraTime);
    argumentsList << QString("%1").arg(memoryLimit);
    runner->setProcessEnvironment(environment);
    runner->setWorkingDirectory(workingDirectory);
    runner->start(workingDirectory + "watcher", argumentsList);
    if (! runner->waitForStarted(-1)) {
        delete runner;
        score = 0;
        result = CannotStartProgram;
        return;
    }
    
    bool flag = false;
    QElapsedTimer timer;
    timer.start();
    
    while (timer.elapsed() <= timeLimit + extraTime) {
        if (runner->state() != QProcess::Running) {
            flag = true;
            break;
        }
        QCoreApplication::processEvents();
        if (stopJudging) {
            runner->terminate();
            runner->waitForFinished(-1);
            delete runner;
            return;
        }
        msleep(10);
    }
    
    if (! flag) {
        runner->terminate();
        runner->waitForFinished(-1);
        delete runner;
        score = 0;
        result = TimeLimitExceeded;
        timeUsed = memoryUsed = -1;
        return;
    }
    
    int code = runner->exitCode();
    
    if (code == 1) {
        delete runner;
        score = 0;
        result = CannotStartProgram;
        timeUsed = memoryUsed = -1;
        return;
    }
    
    if (code == 2) {
        delete runner;
        score = 0;
        result = RunTimeError;
        QFile file(workingDirectory + "_tmperr");
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            message = stream.readAll();
            file.close();
        }
        timeUsed = memoryUsed = -1;
        return;
    }
    
    QString out = QString::fromLocal8Bit(runner->readAllStandardOutput().data());
    QTextStream stream(&out, QIODevice::ReadOnly);
    stream >> timeUsed >> memoryUsed;
    
    if (memoryUsed <= 0) memoryLimit = -1;
    
    if (code == 3) {
        delete runner;
        score = 0;
        result = TimeLimitExceeded;
        timeUsed = -1;
        return;
    }
    
    if (code == 4) {
        delete runner;
        score = 0;
        result = MemoryLimitExceeded;
        memoryUsed = -1;
        return;
    }
    
    delete runner;
#endif
}