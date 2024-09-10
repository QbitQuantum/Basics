//fills in the system folder path in the form \\device\\...
//Input 'plen' points to the number of available bytes in 'path'
//Output 'plen' points to the actual number of bytes fillen in
ULONG GetSystemDirectory(PWCHAR path, PULONG plen)
{

   WCHAR qRes[256]; WCHAR *wc;
   _wcsnset(path, 0, *plen);
   _wcsnset(qRes, 0, 256);
   /*
   QueryRegValue(SYSTEM_PARTITION_KEY, SYSTEM_PARTITION_VALUE, qRes);
   //DbgPrint("Key Data for SysPart = %S\n", qRes);
   wcscpy(path, qRes);
   _wcsnset(qRes, 0, 256);
   */
   QueryRegValue(SYSTEM_ROOT_KEY, SYSTEM_ROOT_VALUE, qRes);
   wcscpy(path, qRes);

   _wcsnset(qRes, 0, 256);

   QueryRegValue(DLL_DIR_KEY, DLL_DIR_VALUE, qRes);
   wc = wcschr(qRes, L'\\');
   if(wc != NULL){
      wcscat(path, L"\\");
      wcscat(path, &wc[1]);
   }
   //DbgPrint("Path = <%S>", path);
   //wcscpy(path, L"\\device\\harddiskvolume2\\WINDOWS\\system32");
   return 1; //success
}