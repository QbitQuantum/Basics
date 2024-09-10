// load JE, Jinit, getprocaddresses, JSM
J jeload(void* callbacks)
{
#ifdef _WIN32
 WCHAR wpath[PLEN];
 MultiByteToWideChar(CP_UTF8,0,pathdll,1+(int)strlen(pathdll),wpath,PLEN);
 hjdll=LoadLibraryW(wpath);
 if (!hjdll) hjdll = LoadLibraryA(JDLLNAME);
#else
 hjdll=dlopen(pathdll,RTLD_LAZY);
 if (!hjdll) hjdll = dlopen(JDLLNAME,RTLD_LAZY);
#endif
 if(!hjdll) return 0;
 jt=((JInitType)GETPROCADDRESS(hjdll,"JInit"))();
 if(!jt) return 0;
 ((JSMType)GETPROCADDRESS(hjdll,"JSM"))(jt,callbacks);
 jdo=(JDoType)GETPROCADDRESS(hjdll,"JDo");
 jfree=(JFreeType)GETPROCADDRESS(hjdll,"JFree");
 jga=(JgaType)GETPROCADDRESS(hjdll,"Jga");
 jgetlocale=(JGetLocaleType)GETPROCADDRESS(hjdll,"JGetLocale");
 return jt;
}