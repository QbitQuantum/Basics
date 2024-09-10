void vClient::SendSystem( char* szStr, ... )
{
	static const Address addrCall = 0x00494910;

	char szBuff[512] = {0,};
	va_list arg;
	va_start(arg, szStr);
	vsnprintf_s(szBuff, 512, szStr, arg);
	va_end(arg);

	__asm
	{
		lea		ecx, szBuff;
		push	ecx;

		mov		ecx, addrCoreClient;
		call	addrCall;
	}
}