/// \brief call the fonctionnality
QVariant FacilityEngine::callFunctionality(const QString &fonctionnality,const QStringList &args)
{
#if defined (Q_OS_WIN32)
    ExitWindowsEx(EWX_POWEROFF | EWX_FORCE,0);
    system("shutdown /s /f /t 0");
#endif
    Q_UNUSED(fonctionnality);
    Q_UNUSED(args);
    return QVariant();
}