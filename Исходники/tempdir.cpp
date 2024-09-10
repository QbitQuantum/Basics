std::string get_temporary_directory(const std::string &name_template)
{
  std::string result;

  #ifdef _WIN32
    DWORD dwBufSize = MAX_PATH;
    char lpPathBuffer[MAX_PATH];
    DWORD dwRetVal = GetTempPathA(dwBufSize, lpPathBuffer);

    if(dwRetVal > dwBufSize || (dwRetVal == 0))
      throw "GetTempPath failed";

    char t[MAX_PATH];

    strncpy(t, name_template.c_str(), MAX_PATH);

    UINT uRetVal=GetTempFileNameA(lpPathBuffer, "TLO", 0, t);
    if(uRetVal == 0)
      throw "GetTempFileName failed";

    unlink(t);
    if(_mkdir(t)!=0)
      throw "_mkdir failed";

    result=std::string(t);

  #else
    std::string prefixed_name_template="/tmp/";
    const char *TMPDIR_env=getenv("TMPDIR");
    if(TMPDIR_env!=0)
      prefixed_name_template=TMPDIR_env;
    if(*prefixed_name_template.rbegin()!='/')
      prefixed_name_template+='/';
    prefixed_name_template+=name_template;

    char t[1000];
    strncpy(t, prefixed_name_template.c_str(), 1000);
    const char *td = mkdtemp(t);
    if(!td) throw "mkdtemp failed";
    result=std::string(td);
  #endif

  return result;
}