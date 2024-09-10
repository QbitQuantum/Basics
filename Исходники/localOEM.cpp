int _cdecl LCSort(const void *el1,const void *el2)
{
	char Str1[]={*reinterpret_cast<const char*>(el1),L'\0'},
		Str2[]={*reinterpret_cast<const char*>(el2),L'\0'};
	OemToCharBuffA(Str1,Str1,1);
	OemToCharBuffA(Str2,Str2,1);
	return(CompareStringA(Opt.LCIDSort,NORM_IGNORENONSPACE|SORT_STRINGSORT|NORM_IGNORECASE,Str1,1,Str2,1)-2);
}