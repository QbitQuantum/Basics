_CRTIMP2_PURE short __CLRCALL_PURE_OR_CDECL _Getwctype(wchar_t _Ch,
	const _Ctypevec *_Ctype)
	{	/* return character classification flags for _Ch */
	_CRT_UNUSED(_Ctype);
	short _Mask;
	return ((short)(GetStringTypeW(CT_CTYPE1, &_Ch, 1,
		(LPWORD)&_Mask) == 0
		? 0 : _Mask));
	}