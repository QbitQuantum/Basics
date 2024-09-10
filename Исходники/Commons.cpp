//---------------------------------------------------------------------------
void StringToTokiensA( AnsiString Words, AnsiString Dlmtr, TStrings *Making )
{
  AnsiString Work = Words.Trim();
  int spos;
  while ((spos = Work.AnsiPos(Dlmtr)) != 0) {
    Making->Add(Work.SubString( 1, spos-1));
    Work = Work.SubString( spos+1, Work.Length() - spos);
    Work = Work.Trim();
  } // while
  if (Work != "")
    Making->Add(Work);
}