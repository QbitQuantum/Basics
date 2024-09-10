 UString GetNextName()
 {
   UString newName;
   int i;
   int numLetters = ChangedPart.Length();
   for (i = numLetters - 1; i >= 0; i--)
   {
     wchar_t c = ChangedPart[i];
     if (c == L'9')
     {
       c = L'0';
       newName = c + newName;
       if (i == 0)
         newName = UString(L'1') + newName;
       continue;
     }
     c++;
     newName = c + newName;
     i--;
     for (; i >= 0; i--)
       newName = ChangedPart[i] + newName;
     break;
   }
   ChangedPart = newName;
   return UnchangedPart + ChangedPart;
 }