// Remove/replace characters from the string so it can be used as an attribute name
// it changes the string that is passed to it.  first leading an trailing spaces
// are removed, then Characters that are invalid in compatible classads 
// (basically anthing but [a-zA-Z0-9_]) is replaced with chReplace.
// if chReplace is 0, then invalid characters are removed. 
// if compact is true, then multiple consecutive runs of chReplace
// are changed to a single instance.
// return value is the length of the resulting string.
//
int cleanStringForUseAsAttr(MyString &str, char chReplace/*=0*/, bool compact/*=true*/)
{
   // have 0 mean 'remove' since we can't actually use it as a replacement char
   // we'll actually implement it by replacing invalid chars with spaces,
   // and then compacting to remove all of the spaces.
   if (0 == chReplace) {
      chReplace = ' ';
      compact = true;
   }

   // trim the input and replace invalid chars with chReplace
   str.trim();
   for (int ii = 0; ii < str.Length(); ++ii) {
      char ch = str[ii];
      if (ch == '_' || (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
         continue;
      str.setChar(ii,chReplace);
      }

   // if compact, convert runs of chReplace with a single instance,
   // unless chReplace is ' ', then remove them entirely.
   if (compact) {
      if (chReplace == ' ')
         str.replaceString(" ","");
      else {
         MyString tmp; tmp += chReplace; tmp += chReplace;
         str.replaceString(tmp.Value(), tmp.Value()+1);
      }
   }
   str.trim();
   return str.Length();
}