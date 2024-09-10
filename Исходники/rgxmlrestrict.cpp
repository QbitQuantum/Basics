RGString RGXmlDataFractionDigits :: BuildString (const RGPScalar& p, int& param1, int& param2) {

	int fractionalDigits = SizeLimit;
	char* str;
	double d = p.GetDouble ();
	int decimalPoint;
	int sign;
	str = fcvt (d, fractionalDigits, &decimalPoint, &sign);
	RGString Result = str;
	param1 = decimalPoint;
	param2 = sign;
	return Result;
}