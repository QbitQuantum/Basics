void ATextHandler::WriteToOthers(const char *fmt, ...)
{
	AString str;
	va_list ap;

	va_start(ap, fmt);
	str.vprintf(fmt, ap);
	va_end(ap);

	const ADataList& clientlist = server.GetClientList();
	uint_t i;
	for (i = 0; i < clientlist.Count(); i++) {
		ATextHandler *handler = (ATextHandler *)clientlist[i];
		
		if (handler != this) {
			handler->senddata += str;
			handler->SendData();
		}
	}
}