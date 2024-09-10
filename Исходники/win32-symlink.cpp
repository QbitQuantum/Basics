static inline UINT
filecp(void)
{
	UINT cp = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	return cp;
}