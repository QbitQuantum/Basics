/// Function name  : verifyScriptFileArgumentName
// Description     : Verifies a ScriptFile argument name is unique and contains no unsupported symbols
// 
// CONST SCRIPT_FILE*  pScriptFile      : [in]           ScriptFile containing the Arguments to check
// CONST TCHAR*        szArgumentName   : [in]           Name to verify
// CONST ARGUMENT*     pExcludeArgument : [in][optional] ScriptFile Argument to exclude from the check (Used when updating the name of an existing argument)
// 
// Return Value   : TRUE if name is unique and contains no unsupported symbols, otherwise FALSE
// 
BearScriptAPI 
BOOL  verifyScriptFileArgumentName(CONST SCRIPT_FILE*  pScriptFile, CONST TCHAR*  szArgumentName, CONST ARGUMENT*  pExcludeArgument)
{
   ARGUMENT*  pArgument;      // ScriptFile ARGUMENT iterator
   BOOL       bResult;        // Verification result

   // [CHECK] Ensure name is not empty or has perculiar symbols
   bResult = lstrlen(szArgumentName) AND !StrPBrk(szArgumentName, TEXT("|!`¬£$%^&*()[]{}-_=+:;@'#~<>,/? \"\\"));

   /// Iterate through ScriptFile's ARGUMENTs
   for (UINT  iArgument = 0; bResult AND findArgumentInScriptFileByIndex(pScriptFile, iArgument, pArgument); iArgument++)
   {
      // [CHECK] Exclude the input Argument (if any) from checking
      if (pArgument == pExcludeArgument)
         continue;

      // [CHECK] Ensure name is unique
      bResult = !utilCompareStringVariables(szArgumentName, pArgument->szName);
   }

   // Return result
   return bResult;
}