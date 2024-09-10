void LIB_DATABASE_EXPORT CaUnicode2Utf8Len(unsigned short* src,int len,char*tar)
{
	unsigned int n;
	n=WideCharToMultiByte(CP_UTF8,0,src,(unsigned int)-1,(unsigned char*)tar,len,0,0);
	tar[n]=0;
}