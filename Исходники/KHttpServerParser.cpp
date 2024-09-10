bool KHttpServerParser::parseString(const char *buf)
{
	KXml xml;
	bool result = false;
	xml.setEvent(this);
	try {		
		result = xml.parseString(buf);
	} catch (KXmlException &e) {
		klog(KLOG_ERR, "%s", e.what());
	}
	return result;
}