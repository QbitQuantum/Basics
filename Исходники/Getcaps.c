void ComplexDeviceCapsLine (char *pbuf, CAPSLOOKUP *pLkUp, int iMaxEntries,
                     int iValue, int iBuffSize)
{
  int  i;
  BOOL bNewLine = FALSE;

  for (i = 0; i < iMaxEntries; i++)

    if (iValue & (pLkUp + i)->iValue)
    {
      if (bNewLine)
      {
        //
        // Keep the first symbolic constant on the same line as the
        //   cap type, eg:  "TECHNOLOGY:     DT_RASDISPLAY".
        //

        strncpy_s (pbuf, iBuffSize, BLANKS, _countof(BLANKS));
        strncat_s (pbuf, iBuffSize, (pLkUp + i)->szValue, _TRUNCATE);
      }
      else
      {
        //
        // Put symbolic constant on new line, eg:
        //                  "                DT_RASPRINTER".
        //

        strncat_s (pbuf, iBuffSize, (pLkUp + i)->szValue, _TRUNCATE);
        bNewLine = TRUE;
      }
      SendDlgItemMessage (ghwndDevCaps, DID_LISTBOX, LB_INSERTSTRING,
                          (UINT)-1, (LONG_PTR) pbuf);
   }
}