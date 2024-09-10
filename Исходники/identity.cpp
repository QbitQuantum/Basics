	RoutingKey CreateRoutingKey (const IdentHash& ident)
	{
		uint8_t buf[41]; // ident + yyyymmdd
		memcpy (buf, (const uint8_t *)ident, 32);
		time_t t = time (nullptr);
		struct tm tm;
		// WARNING!!! check if it is correct
#ifdef _WIN32
		gmtime_s(&tm, &t);
		// тут возвращается какое-то значение sprintf'ом. может стоит его проверять?
		// http://msdn.microsoft.com/en-us/library/ce3zzk1k.aspx
		sprintf_s((char *)(buf + 32), 9, "%4i%2i%2i", tm.tm_year, tm.tm_mon, tm.tm_mday);
#else
		gmtime_r(&t, &tm);
		// тут возвращается какое-то значение sprintf'ом. может стоит его проверять?
		sprintf((char *)(buf + 32), "%4i%2i%2i", tm.tm_year, tm.tm_mon, tm.tm_mday);
#endif		
		RoutingKey key;
		CryptoPP::SHA256().CalculateDigest(key.hash, buf, 40);
		return key;
	}	