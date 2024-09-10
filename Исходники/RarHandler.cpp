 UString GetNextName()
 {
   UString newName; 
   if (_newStyle || !_first)
   {
     int i;
     int numLetters = _changedPart.Length();
     for (i = numLetters - 1; i >= 0; i--)
     {
       wchar_t c = _changedPart[i];
       if (c == L'9')
       {
         c = L'0';
         newName = c + newName;
         if (i == 0)
           newName = UString(L'1') + newName;
         continue;
       }
       c++;
       newName = UString(c) + newName;
       i--;
       for (; i >= 0; i--)
         newName = _changedPart[i] + newName;
       break;
     }
     _changedPart = newName;
   }
   _first = false;
   return _unchangedPart + _changedPart + _afterPart;
 }