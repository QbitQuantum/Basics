//===========================================================================
AnsiString GetShortFileName(AnsiString FileName)
{
   int        SlashCount = 0;
   int        Pos1       = 1111111111;
   int        Pos2       = 0;
   AnsiString Result     = "";

  // --- Считаю количесто слешев -----
   for (int i = 1; i <= FileName.Length(); i++)
       if (FileName[i] == '\\'){
          SlashCount ++;
          if (SlashCount == 2) Pos1 = i;
       }
  // ---- Проверяю количество слешев -------
  if (SlashCount > 3) {
      // ---- Ищу вторую позицию слеша ------
      SlashCount = 0;
      for (int i = FileName.Length(); i > 0; i--){
         if (FileName[i] == '\\'){
            SlashCount ++;
            if (SlashCount == 2 ) {
              Pos2 = i;
              break;
            }
         }
      }

      for (int i = 1; i <= FileName.Length(); i++) {
         if (i <= Pos1) {
               Result = Result + FileName[i];
               if (i + 1 > Pos1) Result = Result + "...";
         }
         if (i >= Pos2) Result = Result + FileName[i];
      }
  } else Result = FileName;

  return Result;
}