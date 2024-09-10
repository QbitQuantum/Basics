/// Checks whether the parameter string consists of a valid IP4 address
/// Requires WinSocket2 library in Windows (ws2_32), not available in Windows XP and below
bool validateAddress(const std::string& address)
{
	unsigned long dummy = 0;
	return 0 != inet_pton(AF_INET, address.c_str(), &dummy);
}