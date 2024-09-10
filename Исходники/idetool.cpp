static WString sSwapCase(const WString& s)
{
	WStringBuffer r;
	r.SetCount(s.GetCount());
	for(int i = 0; i < s.GetCount(); i++)
		r[i] = IsUpper(s[i]) ? ToLower(s[i]) : ToUpper(s[i]);
	return r;
}