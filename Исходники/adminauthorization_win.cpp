bool AdminAuthorization::execute(const QString &program, const QStringList &arguments)
{
    // AdminAuthorization::execute uses UAC to ask for admin privileges. If the user is no
    // administrator yet and the computer's policies are set to not use UAC (which is the case
    // in some corporate networks), the call to execute() will simply succeed and not at all
    // launch the child process. To avoid this, we detect this situation here and return early.
    if (!hasAdminRights())
    {
        QLatin1String key("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
                          "Policies\\System");
        QSettings registry(key, QSettings::NativeFormat);
        const QVariant enableLUA = registry.value(QLatin1String("EnableLUA"));

        if ((enableLUA.type() == QVariant::Int) && (enableLUA.toInt() == 0))
        {
            return false;
        }
    }

    const QString file = QDir::toNativeSeparators(program);
    const QString args = qt_create_commandline(QString(), arguments);

    SHELLEXECUTEINFOW shellExecuteInfo = { 0 };
    shellExecuteInfo.nShow = SW_HIDE;
    shellExecuteInfo.lpVerb = L"runas";
    shellExecuteInfo.lpFile = (wchar_t *)file.utf16();
    shellExecuteInfo.cbSize = sizeof(SHELLEXECUTEINFOW);
    shellExecuteInfo.lpParameters = (wchar_t *)args.utf16();
    shellExecuteInfo.fMask = SEE_MASK_NOASYNC;

    qDebug() << QString::fromLatin1("Starting elevated process %1 with arguments: %2.").arg(file, args);

    if (ShellExecuteExW(&shellExecuteInfo))
    {
        qDebug() << "Finished starting elevated process.";
        return true;
    }
    else
    {
        qWarning() << QString::fromLatin1("Error while starting elevated process: %1, "
            "Error: %2").arg(program, windowsErrorString(GetLastError()));
    }

    return false;
}