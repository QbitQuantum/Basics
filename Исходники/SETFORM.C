// *******************************************************************************
// FUNCTION:     SetEntryField
//
// FUNCTION USE: Set entry field text to field value.
//
// DESCRIPTION:  Convert value to a string, moving decimal point for
//               .01 inch to inch conversion, and set the text of the
//               entry field
//
// PARAMETERS:   HWND     dialog window handle
//               MPARAM   first message parameter
//               MPARAM   second message parameter
//
// RETURNS:      MRESULT  Reserved value of zero
//
// INTERNALS:    NONE
//
// *******************************************************************************
static void SetEntryField( HWND hwnd, ULONG cid, ULONG ulValue, ULONG ulUnits )
{
   char     szText[ 34 ];
   char     *pszTemp;

// --------------------------------------------------------------------------
// Convert the numeric value to a string
// --------------------------------------------------------------------------
   _ltoa( ulValue, szText, 10 );

   if (ulUnits == (ULONG)VSI_INCHES) {

// --------------------------------------------------------------------------
// inches units are actually hundredths - so put in the decimal point
// --------------------------------------------------------------------------
      pszTemp = &szText[ strlen(szText) + 1];
      *pszTemp = *(pszTemp-1);
      pszTemp--;
      *pszTemp = *(pszTemp-1);
      pszTemp--;
      *pszTemp = *(pszTemp-1);
      pszTemp--;
      *pszTemp = '.';
   } /* endif */

// --------------------------------------------------------------------------
// Set the entry field text
// --------------------------------------------------------------------------
   WinSetDlgItemText( hwnd, cid, szText );
}