static int _read_for (FILE* fp, int(*match)(wchar_t), wchar_t* buffer, int ret)
{
	const wchar_t* skip = L" \n\t\r";
	wchar_t c;

	if(buffer==NULL){
		static wchar_t _buffer[1024];
		buffer = _buffer;
	}

	wchar_t* cur = buffer;

	while(wcinrange(c=fgetwc(fp), skip)){}
	ungetwc(c, fp);

	while(!feof(fp)){
		if(!match(c=fgetwc(fp))){
			break;
		}
		*cur++ = c;
	}
	if(ret){
		ungetwc(c, fp);
	}

	if(cur==buffer){
		return 0;
	}else{
		*cur++ = L'\0';
		return 1;
	}
}