CString ExpBase::GetString() const
{
	switch (eType) {
	case EXPTYPE_INTEGER:
		{
			char strbuf[32];
			_i64toa(eData.iVal, strbuf, 10);
			return strbuf;
		}
	case EXPTYPE_FLOAT:
		{
			char strbuf[32];
			_gcvt(eData.fVal, DBL_DIG, strbuf);
			CString str = strbuf;
			if (str.Right(1) == ".")
				str.Delete(str.GetLength() - 1);
			return str;
		}
	case EXPTYPE_STRING:
		return (const char*)*(eData.str);
	case EXPTYPE_ARRAY:
		{
		// Build an expression style array string eg {1, 3, 5, 6}
		CString s = "{";

		ExpStore* ptr = eData.arr.pArray;
		ExpStore* end = eData.arr.pArray + eData.arr.size;
		ExpStore* last = end - 1;

		for ( ; ptr != end; ptr++) {

			bool isString = (ptr->Type() == EXPTYPE_STRING);

			if (isString)
				s += '"';

			s += (const char*)(ptr->GetString());

			if (isString)
				s += '"';

			if (ptr != last)
				s += ", ";
		}

		s += "}";

		return s;
		}
	default:
		return "";
	}
}