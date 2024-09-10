/// Function name  : findNextNonEscapedCharacters
// Description     : Search for the next character occurence of any character in a specified string that is
//                     not preceeded by a backslash.
// 
// CONST TCHAR*  szString      : [in] String to search
// CONST TCHAR*  szCharacters  : [in] String containing the characters to search for
// 
// Return Value   : Position if found, otherwise NULL
// 
CONST TCHAR*  findNextNonEscapedCharacters(CONST TCHAR*  szString, CONST TCHAR*  szCharacters)
{
   CONST TCHAR*  szOutput;

   // Search through all the matching characters in the string
   for (szOutput = StrPBrk(szString, szCharacters); szOutput; szOutput = StrPBrk(szOutput+1, szCharacters))
   {
      // [CHECK] Is first character a match?  Is a subsequent character preceeded by a backslash?
      if (szOutput == szString OR szOutput[-1] != '\\')
         /// [FOUND] Return current position
         return szOutput;  
   }

   /// [NOT FOUND] Return NULL
   return NULL;
}