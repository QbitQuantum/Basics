void Bigint::internalDivide(const Bigint& number, const bool& isDecimal, const int& precision)
{
	std::string mstring;
	std::vector<int> mparts;
	std::string fnvalue = toString();
	std::string snvalue = number.toString();
	if(fnvalue.length()>snvalue.length())
	{
		if(!number.isPositive)
			mstring = snvalue.substr(1);
		else
			mstring = snvalue;
		mparts = parts;
	}
	else
	{
		if(!number.isPositive)
			mstring = fnvalue.substr(1);
		else
			mstring = fnvalue;
		mparts = number.parts;
	}
	if(mstring!="" && mparts.size()>0)
	{
		int recurse = 0;
		std::string build;
		decompose(fnvalue, snvalue, number, recurse, build, isDecimal, precision);
		try {
			create(build);
		} catch (...) {
		}
	}
}