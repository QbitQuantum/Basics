static bool getUL(const VARIANT& v, unsigned long& val)
{
	switch (v.vt) {
		case VT_BSTR: {
			unsigned long ul;
			char c;
			if (swscanf(_bstr_t(v.bstrVal), L" %lu %c", &ul, &c) != 1)
				return false;
			val = ul;
		} break;

		default:
			{
				val = _variant_t(v).operator unsigned long();
				break;
			}
	}
	return true;
}