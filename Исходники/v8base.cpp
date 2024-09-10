	bool _format(cs::String& buf,LPCWSTR fms,...){
		va_list vaList;
		va_start(vaList,fms);
		int bufSize = _vscwprintf(fms,vaList);
		if(bufSize==-1){
			va_end(vaList);
			return 0;
		}
		buf.SetCubage(bufSize+3);
		int n = vswprintf_s(buf,bufSize+1,fms,vaList);
		va_end(vaList);
		return 1;
	}