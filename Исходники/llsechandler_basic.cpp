// retrieve a date structure from an ASN1 time, for 
// validity checking.
LLDate cert_date_from_asn1_time(ASN1_TIME* asn1_time)
{
	
	struct tm timestruct = {0};
	int i = asn1_time->length;
	
	if (i < 10)
	{
		return LLDate();
	}	
	// convert the date from the ASN1 time (which is a string in ZULU time), to
	// a timeval.
	timestruct.tm_year = (asn1_time->data[0]-'0') * 10 + (asn1_time->data[1]-'0');
	
	/* Deal with Year 2000 */
	if (timestruct.tm_year < 70)
		timestruct.tm_year += 100;
	
	timestruct.tm_mon = (asn1_time->data[2]-'0') * 10 + (asn1_time->data[3]-'0') - 1;
	timestruct.tm_mday = (asn1_time->data[4]-'0') * 10 + (asn1_time->data[5]-'0');
	timestruct.tm_hour = (asn1_time->data[6]-'0') * 10 + (asn1_time->data[7]-'0');
	timestruct.tm_min = (asn1_time->data[8]-'0') * 10 + (asn1_time->data[9]-'0');
	timestruct.tm_sec = (asn1_time->data[10]-'0') * 10 + (asn1_time->data[11]-'0');

#if LL_WINDOWS
	return LLDate((F64)_mkgmtime(&timestruct));
#else // LL_WINDOWS
	return LLDate((F64)timegm(&timestruct));
#endif // LL_WINDOWS
}