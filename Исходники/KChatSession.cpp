string_512 KOutgoingMessage::buildTmpFileName() const
{
	char buf[512];
	KDatetime nowDate;
	KLocalDatetime ldt = nowDate.GetLocalTime();
	int n = sprintf_k(buf, sizeof(buf), "%s/tmp/%04d%02d%02d/%d",
		getUserDirectory(),
		ldt.year, ldt.month, ldt.day, m_sequence);
	return string_512(buf, n);
}