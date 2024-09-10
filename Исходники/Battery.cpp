bool Battery::isConenctedToPowerSupply()
{
#if defined Q_OS_WIN
    GetSystemPowerStatus (&power);
    return power.ACLineStatus != 0;
#endif

#if defined Q_OS_MAC
    QByteArray data;
    QProcess process;

    process.start ("pmset -g batt");

    while (process.waitForReadyRead())
        data.append (process.readAll());

    if (data.contains ("discharging"))
        return false;

    return true;
#endif

#if defined Q_OS_LINUX
    QByteArray data;
    QProcess process;

    process.start ("bash -c \"upower -i $(upower -e | grep 'BAT') | "
                   "grep -E 'state|to\\ full|percentage'\"");

    while (process.waitForReadyRead())
        data.append (process.readAll());

    if (data.contains ("discharging"))
        return false;

    return true;
#endif
}