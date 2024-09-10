bool loadConfig(){
    wchar_t inipath[MAX_PATH + 1];
    if(!SUCCEEDED(SHGetFolderPath(NULL,CSIDL_COMMON_APPDATA|CSIDL_FLAG_CREATE, NULL, 0, inipath))) return false;
    wchar_t* path = lstrcat(inipath,L"\\HashingPasswordFilter.ini");
    wchar_t buffer[MAX_PATH + 1];
    if (path==NULL)return false;
    configuration.appsAdmin = loadSetting(path,L"appsAdmin",buffer,MAX_PATH + 1);
    configuration.appsDomain = loadSetting(path,L"appsDomain",buffer,MAX_PATH + 1);
    configuration.appsPasswd = loadSetting(path,L"appsPasswd",buffer,MAX_PATH + 1);
    configuration.ldapAdminBindDn = loadSetting(path,L"ldapAdminBindDn",buffer,MAX_PATH + 1);
    configuration.ldapAdminPasswd = loadSetting(path,L"ldapAdminPasswd",buffer,MAX_PATH + 1);
    configuration.ldapSearchBaseDn = loadSetting(path,L"ldapSearchBaseDn",buffer,MAX_PATH + 1);
    configuration.proxyAddress = loadSetting(path,L"proxyAddress",buffer,MAX_PATH + 1);
    configuration.useProxy = lstrcmp(configuration.proxyAddress,L"")==0?false:true;
    if (configuration.useProxy){
        configuration.proxyUser = loadSetting(path,L"proxyUser",buffer,MAX_PATH + 1);
        configuration.proxyPassword = loadSetting(path,L"proxyPassword",buffer,MAX_PATH + 1);
    } else {
        configuration.proxyUser = L"";
        configuration.proxyPassword = L"";
    }
    wchar_t* temp = loadSetting(path,L"processPath",buffer,MAX_PATH + 1);
    int cmdLineLen = _scwprintf(PROCESS_COMMAND_LINE_FORMAT_STRING,temp,PROCESS_COMMAND_LINE_PARAMETERS,
        configuration.proxyAddress, configuration.proxyUser, configuration.proxyPassword) + 1;
    configuration.processCommandLine = (wchar_t*)malloc(cmdLineLen * sizeof(wchar_t));
    swprintf(configuration.processCommandLine,cmdLineLen,PROCESS_COMMAND_LINE_FORMAT_STRING,temp,
        PROCESS_COMMAND_LINE_PARAMETERS, configuration.proxyAddress, configuration.proxyUser,
        configuration.proxyPassword);
    free(temp);
    configuration.processPasswd = loadSetting(path,L"processPasswd",buffer,MAX_PATH + 1);
    configuration.processUser = loadSetting(path,L"processUser",buffer,MAX_PATH + 1);

    return true;
}