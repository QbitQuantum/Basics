USER_OBJECT_
R_createRegistryKey(USER_OBJECT_ hkey, USER_OBJECT_ subKey)
{
  HKEY lkey, key;
  DWORD created;
  USER_OBJECT_ ans;
  char *name;
  LONG status = ERROR_SUCCESS;

  lkey = getOpenRegKey(hkey, subKey);

  name = CHAR_DEREF(STRING_ELT(subKey, 1));
  status = RegCreateKeyEx(lkey, name, 0, (char *) NULL, 
			  REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &created);
  if(status != ERROR_SUCCESS) {
    char errBuf[1000];
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                     errBuf, sizeof(errBuf)/sizeof(errBuf[0]), NULL);
    RegCloseKey(lkey);
    PROBLEM "Can't create key %s: %s", name, errBuf
    ERROR;
  }

  ans = NEW_LOGICAL(1);
  if(created == REG_OPENED_EXISTING_KEY ) {
    RegCloseKey(key);
  } else {
    RegFlushKey(key);
    LOGICAL_DATA(ans)[0] = TRUE;
  }

  RegCloseKey(lkey);

  return(ans);
}