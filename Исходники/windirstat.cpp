LANGID CDirstatApp::GetEffectiveLangid()
{
	if (GetOptions()->IsUseWdsLocale())
		return GetLangid();
	else
		return GetUserDefaultLangID();
}