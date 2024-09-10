  struct _WIN32_FIND_DATAA FindFileData; // [sp+214h] [bp-454h]@1
  int v11; // [sp+354h] [bp-314h]@30
  char *v12; // [sp+358h] [bp-310h]@44
  char v13; // [sp+35Ch] [bp-30Ch]@44
  char v14; // [sp+4BCh] [bp-1ACh]@4
  unsigned __int8 v15; // [sp+4C2h] [bp-1A6h]@7
  unsigned __int8 v16; // [sp+4D7h] [bp-191h]@4
  unsigned __int8 v17; // [sp+4D8h] [bp-190h]@5
  int j; // [sp+660h] [bp-8h]@1
  HANDLE hFindFile; // [sp+664h] [bp-4h]@1

  v5 = this;
  sprintf(globBuf, "%s%s", a2, a3);
  *(_DWORD *)((char *)v5 + 1042) = 0;
  j = 1;
  hFindFile = FindFirstFileA(globBuf, &FindFileData);
  if ( hFindFile != (HANDLE)-1 )
  {
    while ( j )
    {
      if ( *(_DWORD *)((char *)v5 + 66) != 1
        || (sub_40B430((int)FindFileData.cFileName, &v14), v16 <= dword_5235D4)
        && v17 >= dword_5235D4
        && (dword_4EDE90 == 4 || (unsigned __int8)byte_4F19D0[dword_4EDE90] == v15)
        && sub_40B4D0() )
      {
        if ( *(_DWORD *)((char *)v5 + 66) != 4
          || ((sub_40B430((int)FindFileData.cFileName, &v14), dword_4EDE90 == 4)
           || (unsigned __int8)byte_4F19D0[dword_4EDE90] == v15)
          && unknown_libname_3() )
          ++*(_DWORD *)((char *)v5 + 1042);