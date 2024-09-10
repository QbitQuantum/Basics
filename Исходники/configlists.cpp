void ConfigLists::msgCallback(CSOUND *csound, int attr, const char *fmt, va_list args)
{
	Q_UNUSED(attr);
	QString *ud = (QString *) csoundGetHostData(csound);
	QString msg;
	msg = msg.vsprintf(fmt, args);
	if (msg.isEmpty()) {
		return;
	}
	ud->append(msg);
}