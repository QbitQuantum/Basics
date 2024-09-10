void KadUDPKey::fromInt64String(char *str)
{
#ifdef WIN32
	__int64 key_num;
	key_num = _atoi64(str);
#else
	long long key_num;
	key_num = atoll(str);
#endif
	m_dwKey = key_num >> 32;
	m_dwIP = key_num&(-1);
}