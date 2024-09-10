wchar_t *ExciteWindow::GetTranslationPath(Language src, Language dst, const wchar_t *text)
{
	if (src != LANGUAGE_Japanese && dst != LANGUAGE_Japanese || src == dst)
		return NULL;
	const wchar_t *p;
	switch (dst != LANGUAGE_Japanese ? dst : src)
	{
		case LANGUAGE_English:
			p = L"/world/english_japanese/"; break;
		case LANGUAGE_Chinese_Simplified:
		case LANGUAGE_Chinese_Traditional:
			p = L"/world/chinese/"; break;
		case LANGUAGE_Korean:
			p = L"/world/korean/"; break;
		case LANGUAGE_French:
			p = L"/world/french/"; break;
		case LANGUAGE_German:
			p = L"/world/german/"; break;
		case LANGUAGE_Italian:
			p = L"/world/italian/"; break;
		case LANGUAGE_Spanish:
			p = L"/world/spanish/"; break;
		case LANGUAGE_Portuguese:
			p = L"/world/portuguese/"; break;
		case LANGUAGE_Russian:
			p = L"/world/russian/"; break;
		default:
			return NULL;
	}
	return _wcsdup(p);
}