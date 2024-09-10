void Filesets_Dump_OnInitDialog (HWND hDlg, LPSET_DUMP_PARAMS psdp)
{
   TCHAR szServer[ cchNAME ];
   TCHAR szAggregate[ cchNAME ];
   TCHAR szFileset[ cchNAME ];
   psdp->lpi->GetServerName (szServer);
   psdp->lpi->GetAggregateName (szAggregate);
   psdp->lpi->GetFilesetName (szFileset);

   TCHAR szText[ cchRESOURCE ];
   GetDlgItemText (hDlg, IDC_DUMP_FULL, szText, cchRESOURCE);

   LPTSTR pszText = FormatString (szText, TEXT("%s%s%s"), szServer, szAggregate, szFileset);
   SetDlgItemText (hDlg, IDC_DUMP_FULL, pszText);
   FreeString (pszText);

   pszText = FormatString (IDS_SET_DUMP_NAME, TEXT("%s"), szFileset);
   SetDlgItemText (hDlg, IDC_DUMP_FILENAME, pszText);
   FreeString (pszText);

   // Get the local system time
   SYSTEMTIME st;
   GetSystemTime (&st);
   FILETIME ft;
   SystemTimeToFileTime (&st, &ft);
   FILETIME lft;
   FileTimeToLocalFileTime (&ft, &lft);
   FileTimeToSystemTime (&lft, &st);

   DA_SetDate (GetDlgItem (hDlg, IDC_DUMP_DATE), &st);
   TI_SetTime (GetDlgItem (hDlg, IDC_DUMP_TIME), &st);

   CheckDlgButton (hDlg, IDC_DUMP_FULL, TRUE);
   Filesets_Dump_OnSelect (hDlg);
   Filesets_Dump_EnableOK (hDlg);
}