void ETWLogger::err(const std::string& msg) {
	EVENT_DATA_DESCRIPTOR descr;
	EventDataDescCreate(&descr, msg.c_str(), static_cast<ULONG>(msg.size()));
	auto status = EventWrite(
		m_registration_handle,
		&ErrEvent,
		1,
		&descr
		);
	if (status != 0) DebugBreak();
}