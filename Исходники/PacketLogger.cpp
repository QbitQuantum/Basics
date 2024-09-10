const char* PacketLogger::UserIDTOString(unsigned char Id)
{
	// Users should override this
	static char str[256];
	Itoa(Id, str, 10);
	return (const char*) str;
}