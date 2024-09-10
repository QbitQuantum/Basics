CXTPMarkupObject* CXTPMarkupThickness::ConvertFrom(CXTPMarkupBuilder *pBuilder, CXTPMarkupObject* pObject) const
{
	UNREFERENCED_PARAMETER(pBuilder);

	if (IsStringObject(pObject))
	{
		LPCWSTR lpszValue = *((CXTPMarkupString*)pObject);
		int nLength = ((CXTPMarkupString*)pObject)->GetLength();

		if (wcschr(lpszValue, L',') == NULL)
		{
			int nThickness = _wtoi(lpszValue);

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"pt") == 0)
			{
				return new CXTPMarkupThickness(MulDiv(nThickness, 96, 72));
			}

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"in") == 0)
			{
				return new CXTPMarkupThickness(nThickness * 96);
			}

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"cm") == 0)
			{
				return new CXTPMarkupThickness(int((double)nThickness * 37.79528));
			}

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"mm") == 0)
			{
				return new CXTPMarkupThickness(int((double)nThickness * 3.779528));
			}

			return new CXTPMarkupThickness(nThickness);
		}
		else
		{
			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"pt") == 0)
			{
				int left = 0, top = 0, right = 0, bottom = 0;
				if ( WSCANF_S(lpszValue, L"%ipt, %ipt, %ipt, %ipt", &left, &top, &right, &bottom) != 4)
					return NULL;

				return new CXTPMarkupThickness(MulDiv(left, 96, 72), MulDiv(top, 96, 72), MulDiv(right, 96, 72), MulDiv(bottom, 96, 72));
			}

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"in") == 0)
			{
				int left = 0, top = 0, right = 0, bottom = 0;
				if ( WSCANF_S(lpszValue, L"%iin, %iin, %iin, %iin", &left, &top, &right, &bottom) != 4)
					return NULL;

				return new CXTPMarkupThickness(left * 96, top * 96, right * 96, bottom * 96);
			}

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"cm") == 0)
			{
				int left = 0, top = 0, right = 0, bottom = 0;
				if ( WSCANF_S(lpszValue, L"%icm, %icm, %icm, %icm", &left, &top, &right, &bottom) != 4)
					return NULL;

				return new CXTPMarkupThickness(int((double)left * 37.79528), int((double)top * 37.79528), int((double)right * 37.79528), int((double)bottom * 37.79528));
			}

			if ((nLength > 2) && _wcsicmp(lpszValue + nLength - 2, L"mm") == 0)
			{
				int left = 0, top = 0, right = 0, bottom = 0;
				if ( WSCANF_S(lpszValue, L"%imm, %imm, %imm, %imm", &left, &top, &right, &bottom) != 4)
					return NULL;

				return new CXTPMarkupThickness(int((double)left * 3.779528), int((double)top * 3.779528), int((double)right * 3.779528), int((double)bottom * 3.779528));
			}

			int left = 0, top = 0, right = 0, bottom = 0;
			if ( WSCANF_S(lpszValue, L"%i, %i, %i, %i", &left, &top, &right, &bottom) != 4)
				return NULL;

			return new CXTPMarkupThickness(left, top, right, bottom);
		}

	}

	return NULL;
}