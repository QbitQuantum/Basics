void EventLogChannel::log(const Message& msg)
{
	if (!_h) open();
#if defined(POCO_WIN32_UTF8)
	std::wstring utext;
	UnicodeConverter::toUTF16(msg.getText(), utext);
	const wchar_t* pMsg = utext.c_str();
	ReportEventW(_h, getType(msg), getCategory(msg), POCO_MSG_LOG, NULL, 1, 0, &pMsg, NULL); 
#else
	const char* pMsg = msg.getText().c_str();
	ReportEvent(_h, getType(msg), getCategory(msg), POCO_MSG_LOG, NULL, 1, 0, &pMsg, NULL); 
#endif
}