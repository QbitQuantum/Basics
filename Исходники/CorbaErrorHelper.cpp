//-----------------------------------------------------------------------------//
std::string CCorbaErrorHelper::ToString(const CORBA::SystemException& err)
{
	std::string errDescription;
	TCHAR buf[50];
	memset(buf, 0, sizeof(TCHAR) * 50);
	
	CORBA::Any tmp;
	tmp <<= err;
	CORBA::TypeCode_var tc = tmp.type();

	errDescription = std::string(tc->name()) + _T(" Description: ") + err.NP_minorString();
	errDescription += _T(" Minor code: ");
	errDescription += _ltoa_s(err.minor(), buf, 50, 10);

	return errDescription;
}