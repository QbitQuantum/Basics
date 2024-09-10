BOOL UrlDecodeUTF8(LPCWSTR src, DWORD srcSize, wstring& dest)
{
	if( src == NULL ){
		return FALSE;
	}

	string utf8;
	for( DWORD i=0; i<srcSize; i++ ){
		if( src[i] == '%' ){
			if( i+2 > srcSize ){
				break;
			}
			WCHAR tmp[3]=L"";
			tmp[0] = (char)src[i+1];
			tmp[1] = (char)src[i+2];

			WCHAR *endstr;
			char tmp2[2]="";
			tmp2[0] = (char)wcstol(tmp, &endstr, 16);
			utf8 += tmp2;

			i+=2;
		}else if( src[i] == '+' ){
			utf8 += " ";
		}else if( src[i] == '\0' ){
			break;
		}else{
			char tmp[2]="";
			tmp[0] = (char)src[i];
			utf8 += tmp;
		}
	}

	int iLen = MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), -1, NULL, 0 );
	WCHAR* pwszBuff = new WCHAR[iLen+1];
	ZeroMemory(pwszBuff, sizeof(WCHAR)*(iLen+1));
	MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), -1, pwszBuff, iLen );

	dest = pwszBuff;
	
	delete[] pwszBuff;

	return TRUE;
}