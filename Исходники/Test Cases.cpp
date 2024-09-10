/// Configuration  : TESTING
/// Function name  : checkCommandTranslation
// Description     : Check whether the translation of a command matches a specified string
// 
// CONST LIST*   pCommandList   : [in] List of translated COMMAND objects found in a ScriptFile
// CONST UINT    iIndex         : [in] Index of the COMMAND to verify
// CONST TCHAR*  szTranslation  : [in] String to verify the COMMAND translation against
// 
// Return Value   : TRUE if successfully verified, FALSE otherwise
// 
BOOL  checkCommandTranslation(CONST LIST* pCommandList, CONST UINT  iIndex, CONST TCHAR*  szTranslation)
{
   LIST_ITEM*  pListItem;  // ListItem wrapper
   COMMAND*    pCommand;   // Translated COMMAND to check
   BOOL        bResult;    // Verification result

   // Prepare
   bResult = FALSE;

   /// Lookup COMMAND
   if (findListItemByIndex(pCommandList, iIndex, pListItem))
   {
      // Extract COMMAND
      pCommand = (COMMAND*)pListItem->oData;

      /// Check translation
      bResult = (StrCmpI(szTranslation, pCommand->szBuffer) == 0);

      // [FAILED] Print out desired and actual translation
      if (!bResult)
         CONSOLE("ERROR: Command '%s' incorrectly translated as '%s'", szTranslation, pCommand->szBuffer);
   }
   // [ERROR] Command not translated
   else
      CONSOLE("ERROR: Command '%s' (index %u) was not present", szTranslation, iIndex);
   
   /// Return result
   return bResult;
}