void cSocketInputStream::Error(const AString & a_ErrorMsg)
{
	send(m_Socket, a_ErrorMsg.c_str(), static_cast<int>(a_ErrorMsg.length()), 0);
	static const char EndLine[] = "\n";
	send(m_Socket, EndLine, sizeof(EndLine) - 1, 0);

}