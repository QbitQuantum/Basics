String ColorProfile::GetProfileInfo()
{
//	String name= GetProductName();
	String desc= GetProductDesc();
	String info= GetProductInfo();
	String cpyr= GetCopyrightStr();

	oStringstream ost;
	const TCHAR* space= _T("\r\n");
//	ost << name;
//	if (!name.empty())
//		ost << space;
	if (!desc.empty()) // && desc != name)
		ost << desc << space;
	if (!info.empty() && info != desc)// && info != name)
		ost << info << space;
	if (!cpyr.empty() && cpyr != desc && /*cpyr != name &&*/ cpyr != info)
		ost << cpyr << space;

	String str= ost.str();

	while (str[0] == _T(' '))
		str.erase(0);

//	while (!str.empty() && str[str.size() - 1] == _T(' '))
//		str.erase(str.size() - 1);

	return str;
}