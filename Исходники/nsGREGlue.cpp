PRBool
GRE_GetPathFromRegKey(HKEY aRegKey,
                      const GREVersionRange *versions,
                      PRUint32 versionsLength,
                      const GREProperty *properties,
                      PRUint32 propertiesLength,
                      char* aBuffer, PRUint32 aBufLen)
{
  // Formerly, GREs were registered at the registry key
  // HKLM/Software/mozilla.org/GRE/<version> valuepair GreHome=Path.
  // Nowadays, they are registered in any subkey of
  // Software/mozilla.org/GRE, with the following valuepairs:
  //   Version=<version> (REG_SZ)
  //   GreHome=<path>    (REG_SZ or REG_EXPAND_SZ)
  //   <Property>=<value> (REG_SZ)
  //
  // Additional meta-info may be available in the future, including
  // localization info and other information which might be pertinent
  // to selecting one GRE over another.
  //
  // When a GRE is being registered, it should try to register itself at
  // HKLM/Software/mozilla.org/GRE/<Version> first, to preserve compatibility
  // with older glue. If this key is already taken (i.e. there is more than
  // one GRE of that version installed), it should append a unique number to
  // the version, for example:
  //   1.1 (already in use), 1.1_1, 1.1_2, etc...

  DWORD i = 0;

  while (PR_TRUE) {
    char name[MAXPATHLEN + 1];
    DWORD nameLen = MAXPATHLEN;
    if (::RegEnumKeyEx(aRegKey, i, name, &nameLen, NULL, NULL, NULL, NULL) !=
        ERROR_SUCCESS) {
      break;
    }

    HKEY subKey = NULL;
    if (::RegOpenKeyEx(aRegKey, name, 0, KEY_QUERY_VALUE, &subKey) !=
        ERROR_SUCCESS) {
      continue;
    }

    char version[40];
    DWORD versionlen = 40;
    char pathbuf[MAXPATHLEN];
    DWORD pathlen;
    DWORD pathtype;

    PRBool ok = PR_FALSE;

    if (::RegQueryValueEx(subKey, "Version", NULL, NULL,
                          (BYTE*) version, &versionlen) == ERROR_SUCCESS &&
        CheckVersion(version, versions, versionsLength)) {

      ok = PR_TRUE;
      const GREProperty *props = properties;
      const GREProperty *propsEnd = properties + propertiesLength;
      for (; ok && props < propsEnd; ++props) {
        pathlen = sizeof(pathbuf);

        if (::RegQueryValueEx(subKey, props->property, NULL, &pathtype,
                              (BYTE*) pathbuf, &pathlen) != ERROR_SUCCESS ||
            strcmp(pathbuf, props->value))
          ok = PR_FALSE;
      }

      pathlen = sizeof(pathbuf);
      if (ok &&
          (!::RegQueryValueEx(subKey, "GreHome", NULL, &pathtype,
                              (BYTE*) pathbuf, &pathlen) == ERROR_SUCCESS ||
           !*pathbuf ||
           !CopyWithEnvExpansion(aBuffer, pathbuf, aBufLen, pathtype))) {
        ok = PR_FALSE;
      }
      else if (!safe_strncat(aBuffer, "\\" XPCOM_DLL, aBufLen) ||
               access(aBuffer, R_OK)) {
        ok = PR_FALSE;
      }
    }

    RegCloseKey(subKey);

    if (ok)
      return PR_TRUE;

    ++i;
  }

  aBuffer[0] = '\0';

  return PR_FALSE;
}