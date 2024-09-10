SuDate* unpack_old_date(const unsigned char* p)
	{
	DateTime dt = unpack_old_datetime(p);
	return new SuDate(dt.date(), dt.time());
	}