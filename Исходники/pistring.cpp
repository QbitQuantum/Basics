bool operator>=(const string& str1,const char* str2){
	return (str1.comparestr(str2,0,str1.datalen,0,str1.strlen(str2))>=0);}