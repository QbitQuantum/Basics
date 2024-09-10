var& var::operator+=(const ulong& rhs)
{
	if(vt == DW)
		dw += rhs;
	else if(vt == FLT)
		flt += rhs;
	else if(vt == STR) {
		wstring s;
		wchar_t dwbuf[12];
		if (isbuf) {
			//Concate Num ulong to a buffer (4 octets)
			s = strbuffhex();
			wsprintf(dwbuf, L"%08X",rev(rhs));
			*this = L"#" + s + dwbuf + L"#";
		} else {
			//Add Number to a String
			s = _wcsupr(_ultow(rhs, dwbuf, 16));
			str += s;
			size += s.length();
		}
	}
	return *this;
}