static void FreeSidEx(PSID oSID)
{
	try
	{
		FreeSid(oSID);
	} catch (...)
	{
	}
}