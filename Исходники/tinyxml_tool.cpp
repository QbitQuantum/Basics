bool tinyxml_tool::get_int64_attribute(TiXmlElement* pElm, const char* name, long long& v)
{
	if(!pElm) return false;
	const char* pv = pElm->Attribute(name);
	if(!pv) return false;
#ifdef _WIN32
    v = _atoi64(pv);
#else
    v = atol(pv);
#endif
	return true;
}