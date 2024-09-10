void QMPlay2CoreClass::suspend()
{
#if defined Q_OS_LINUX
	Q_UNUSED(system("systemctl suspend > /dev/null 2>&1 &"));
#elif defined Q_OS_WIN
	SetSuspendState(false, false, false);
#elif defined Q_OS_MACOS
	Q_UNUSED(system("pmset sleepnow > /dev/null 2>&1 &"));
#endif
}