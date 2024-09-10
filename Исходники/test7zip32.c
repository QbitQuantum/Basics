int main(int argc, char *argv[])
{
  HANDLE hDLL = LoadLibrary(L"7-zip32");
  if (hDLL != NULL){
      GETPROCADDRESS(WINAPI_SEVENZIP, hZip, "SevenZip");
      GETPROCADDRESS(WINAPI_SEVENZIPGETVERSION, hVersion, "SevenZipGetVersion");
      GETPROCADDRESS(WINAPI_SEVENZIPGETSUBVERSION, hSubVersion, "SevenZipGetSubVersion");
      GETPROCADDRESS(WINAPI_SEVENZIPCHECKARCHIVE, hChkFunc, "SevenZipCheckArchive");
      GETPROCADDRESS(WINAPI_SEVENZIPGETARCHIVETYPE, hArchTypeFunc, "SevenZipGetArchiveType");
      GETPROCADDRESS(WINAPI_SEVENZIPOPENARCHIVE, hOpenFunc, "SevenZipOpenArchive");
      GETPROCADDRESS(WINAPI_SEVENZIPCLOSEARCHIVE, hCloseFunc, "SevenZipCloseArchive");
      GETPROCADDRESS(WINAPI_SEVENZIPSETDEFAULTPASSWORD, hSetDefPasswd, "SevenZipSetDefaultPassword");
      GETPROCADDRESS(WINAPI_SEVENZIPGETFILECOUNT, hFileCount, "SevenZipGetFileCount");
      GETPROCADDRESS(WINAPI_SEVENZIPGETATTRIBUTE, hAttribute, "SevenZipGetAttribute");
      GETPROCADDRESS(WINAPI_SEVENZIPQUERYFUNCTIONLIST, hQueryFunc, "SevenZipQueryFunctionList");

      DWORD dwVersion;
      dwVersion = hVersion();
      DWORD dwSubVersion;
      dwSubVersion = hSubVersion();
      /* 256*3+16*9+8 = 920 -> 9.20 */
      DWORD dwHi = dwVersion & 0x0000ffff;
      g_print("%08lx\n", dwHi);
      DWORD dwLow = (dwSubVersion & 0x0000ffff);
      g_print("%08lx\n", dwLow);

      BOOL bCheck;
      int nType;
      HARC hArch;
      int nAttr;
      int nResult;
      bCheck = hQueryFunc(ISARC_GET_ATTRIBUTE);
      g_print("bCheck:%08x\n", bCheck);
      char buf[1024];
      DWORD dwSize = 0;
      {
          nResult = hZip(NULL, "x hpasswd.7z -aoa -p\"foo\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("hpasswd.7z invalid password nResult:%08x\n", nResult);
      }
      {
          nResult = hZip(NULL, "x hpasswd.7z -aoa -p\"\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("hpasswd.7z blank password nResult:%08x\n", nResult);
      }
      {
          nResult = hZip(NULL, "x hpasswd.7z -aoa -p\"test\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("hpasswd.7z test password nResult:%08x\n", nResult);
      }

      {
          nResult = hZip(NULL, "x passwd.7z -aoa -p\"foo\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("passwd.7z invalid password passwd.7z nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x passwd.7z -aoa -p\"test\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("passwd.7z test password passwd.7z nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x passwd.7z -aoa -p\"\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("passwd.7z blank password passwd.7z nResult:%08x\n", nResult);
      }

      {
          nResult = hZip(NULL, "x passwd.zip -aoa -p\"\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("passwd.zip blank password nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x passwd.zip -aoa -p\"test\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("passwd.zip test password nResult:%08x\n", nResult);
          nResult = hZip(NULL, "x passwd.zip -aoa -p\"foo\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("passwd.zip invalid password nResult:%08x\n", nResult);
      }

      {
          nResult = hZip(NULL, "x nopasswd.zip -aoa -p\"\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("nopasswd.zip blank password nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x nopasswd.zip -aoa -p\"foo\" -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("nopasswd.zip invalid password nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x nopasswd.zip -aoa -hide -oc:\\Temp\\7zip -r", buf, dwSize);
          g_print("nopasswd.zip no password nResult:%08x\n", nResult);
      }

      {
          nResult = hZip(NULL, "x passwd2.zip -aoa -p\"\" -hide -oc:\\Temp\\7zip -r-", buf, dwSize);
          g_print("passwd2.zip blank password nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x passwd2.zip -aoa -p\"foo\" -hide -oc:\\Temp\\7zip -r-", buf, dwSize);
          g_print("passwd2.zip invalid password nResult:%08x\n", nResult);

          nResult = hZip(NULL, "x passwd2.zip -aoa -p\"test\" -hide -oc:\\Temp\\7zip -r-", buf, dwSize);
          g_print("passwd2.zip no password nResult:%08x\n", nResult);
      }

      return 0;
      {
          /*
           * check hpasswd.7z
           */
          nResult = hSetDefPasswd(NULL, "test");
          hArch = hOpenFunc(NULL, "hpasswd.7z", M_ERROR_MESSAGE_OFF|M_BAR_WINDOW_OFF);
          if (hArch != NULL){
              bCheck = hChkFunc("hpasswd.7z", CHECKARCHIVE_BASIC);
              nType = hArchTypeFunc("hpasswd.7z");
              nAttr = hAttribute(hArch);
              /*hArch = hOpenFunc(NULL, "hpasswd.7z", 0);*/
              g_print("nResult:%08x\n", nResult);
              g_print("bCheck:%08x\n", bCheck);
              g_print("nType:%08x\n", nType);
              g_print("nAttr:%08x\n", nAttr);
              if (hArch != NULL && (nAttr & 0x40)){
                  g_print("may be header encrypted\n");
              }
              hCloseFunc(hArch);
          }else{
              g_print("?\n");
          }
      }
      {
          /*
           * check passwd.7z
           */
          bCheck = hChkFunc("passwd.7z", CHECKARCHIVE_BASIC);
          nType = hArchTypeFunc("passwd.7z");
          hArch = hOpenFunc(NULL, "passwd.7z", 0);
          nAttr = hAttribute(hArch);
          g_print("nAttr:%08x\n", nAttr);
          if (bCheck == TRUE && nType == 2 && hArch != NULL && nAttr & 0x40){
              g_print("passwd.7z password encrypted\n");
          }
          hCloseFunc(hArch);
      }
      {
          /*
           * check passwd.zip
           */
          nResult = hSetDefPasswd(NULL, "foo");
          bCheck = hChkFunc("passwd.zip", CHECKARCHIVE_BASIC);
          nType = hArchTypeFunc("passwd.zip");
          hArch = hOpenFunc(NULL, "passwd.zip", 0);
          g_print("hArch:%p\n", hArch);
          nAttr = hAttribute(hArch);
          g_print("bCheck:%08x\n", bCheck);
          g_print("nType:%08x\n", nType);
          g_print("nAttr:%08x\n", nAttr);
          if (bCheck == TRUE && nType == 1 && hArch != NULL && nAttr & 0x40){
              g_print("passwd.zip password encrypted\n");
          }
          hCloseFunc(hArch);
      }
      {
          /*
           * check nopasswd.zip
           */
          nResult = hSetDefPasswd(NULL, "foo");
          bCheck = hChkFunc("nopasswd.zip", CHECKARCHIVE_BASIC);
          nType = hArchTypeFunc("nopasswd.zip");
          hArch = hOpenFunc(NULL, "nopasswd.zip", 0);
          g_print("hArch:%p\n", hArch);
          nAttr = hAttribute(hArch);
          g_print("bCheck:%08x\n", bCheck);
          g_print("nType:%08x\n", nType);
          g_print("nAttr:%08x\n", nAttr);
          if (bCheck == TRUE && nType == 1 && hArch != NULL && nAttr & 0x40){
              g_print("nopasswd.zip password encrypted\n");
          }
      }
      return 0;
  }
  return 0;
}