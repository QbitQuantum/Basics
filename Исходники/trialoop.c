static void PrintPhaseCode(T_PhaseCode *code)
{
  int      iCT, iTab;

  static int TabSymbol[] =
   {
     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     '-', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a',
     '0'
   };


  Fprintf(stdout, "PhaseCode(");

  for (iCT = 0; iCT < nActivePhase; iCT++)
  {
    if (iCT % 72 == 0) putc('\n', stdout);

        iTab = (code[iCT] + 9) / 18;
    if (iTab >= 0 && iTab < (sizeof TabSymbol / sizeof (*TabSymbol)))
      putc(TabSymbol[iTab], stdout);
    else
      putc('~', stdout);
  }

  Fprintf(stdout, "\n)");
}