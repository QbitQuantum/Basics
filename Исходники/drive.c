BOOL
SH_ShowDriveProperties(WCHAR * drive, LPCITEMIDLIST pidlFolder, LPCITEMIDLIST * apidl)
{
   HPSXA hpsx = NULL;
   HPROPSHEETPAGE hpsp[MAX_PROPERTY_SHEET_PAGE];
   PROPSHEETHEADERW psh;
   BOOL ret;
   UINT i;
   WCHAR szName[MAX_PATH+6];
   DWORD dwMaxComponent, dwFileSysFlags;
   IDataObject * pDataObj = NULL;
   UINT DriveType;

   ZeroMemory(&psh, sizeof(PROPSHEETHEADERW));
   psh.dwSize = sizeof(PROPSHEETHEADERW);
   //psh.dwFlags = PSH_USECALLBACK | PSH_PROPTITLE;
   psh.hwndParent = NULL;
   psh.u2.nStartPage = 0;
   psh.u3.phpage = hpsp;

   if (GetVolumeInformationW(drive, szName, sizeof(szName)/sizeof(WCHAR), NULL, &dwMaxComponent,
                             &dwFileSysFlags, NULL, 0))
   {
      psh.pszCaption = szName;
      psh.dwFlags |= PSH_PROPTITLE;
      if (!wcslen(szName))
      {
          /* FIXME
           * check if disk is a really a local hdd 
           */
          i = LoadStringW(shell32_hInstance, IDS_DRIVE_FIXED, szName, sizeof(szName)/sizeof(WCHAR)-6);
          if (i > 0 && i < (sizeof(szName)/sizeof(WCHAR)) - 6)
          {
              szName[i] = L' ';
              szName[i+1] = L'(';
              wcscpy(&szName[i+2], drive);
              szName[i+4] = L')';
              szName[i+5] = L'\0';
          }
      }
   }

   DriveType = GetDriveTypeW(drive);
   for (i = 0; i < DRIVE_PROPERTY_PAGES; i++)
   {
       if (PropPages[i].DriveType == (UINT)-1 || (PropPages[i].DriveType != (UINT)-1 &&  PropPages[i].DriveType == DriveType))
       {
           HPROPSHEETPAGE hprop = SH_CreatePropertySheetPage(PropPages[i].resname, PropPages[i].dlgproc, (LPARAM)drive, NULL);
           if (hprop)
           {
              hpsp[psh.nPages] = hprop;
              psh.nPages++;
           }
       }
   }

   if (SHCreateDataObject(pidlFolder, 1, apidl, NULL, &IID_IDataObject, (void**)&pDataObj) == S_OK)
   {
       hpsx = SHCreatePropSheetExtArrayEx(HKEY_CLASSES_ROOT, L"Drive", MAX_PROPERTY_SHEET_PAGE-DRIVE_PROPERTY_PAGES, pDataObj);
       if (hpsx)
       {
           SHAddFromPropSheetExtArray(hpsx, (LPFNADDPROPSHEETPAGE)AddPropSheetPageProc, (LPARAM)&psh);
       }
   }

   ret = PropertySheetW(&psh);
   if (pDataObj)
       IDataObject_Release(pDataObj);

   if (hpsx)
       SHDestroyPropSheetExtArray(hpsx);

   if (ret < 0)
       return FALSE;
   else
       return TRUE;
}