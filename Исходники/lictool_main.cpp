int _tmain (int argc, _TCHAR **argv)
{

  for (int i = 0; i < argc; ++i)
  {
      out << argv[i] << std::endl;
  }

  if (argc < 2)
  {
    showHelp ();
    return (0);
  }

  params_t params;

  if (!parseCmdLine (argc - 1, argv + 1, &params))
  {
    if (otUnknown == params.opType) 
    {
      out << _T (" : unknown operation") << std::endl;
    }
    else
    {
      out << _T ("bad command line") << std::endl;
    }
    return (-1);
  }

  if (FAILED (initLicensing (AppInfo, params.basesPaths, CLicensingPolicy::cmKeyOnly))) 
  {
    return (-1);
  }

//  synchronizeKeys (AppInfo, KeyFile1, 0);

#if defined (_WIN32)
  SetThreadLocale (MAKELCID (MAKELANGID (LANG_ENGLISH, SUBLANG_NEUTRAL), SORT_DEFAULT));
  CComLib comLib;
#endif

  switch(params.opType) 
  {
    case otKeyReg             : 
    case otKeyRegAdd          : regKey (params.keyFileName, params.keyAddMode); break;
    case otKeyRevoke          : revokeKey (params.serialNumber); break;
    case otCheckActiveKey     :	checkActiveKey (); break;
    case otKeyFileInfo        : keyFileInfo (params.keyFileName); break;
    case otViewInstalledKeys  : viewInstalledKeys (); break;
    case otViewBlacklist      : viewBlacklist (params.blacklistName); break;
    case otCheckAgainstBlacklist: checkAgainstBlackList (params.blacklistName.c_str ()); break;
    case otCheckKeyBlacklist  : checKeyBlacklist (params.keyFileName, params.blacklistName); break;
    case otCheckKeyFile       : 
    case otCheckKeyFileAdd    : 
        checkKeyFile (params.keyFileName, params.keyAddMode); break;
    default                   : break;
  }

//  recreateTest (AppInfo, params.basesPaths, CLicensingPolicy::cmFullCheck);

  return (0);

}