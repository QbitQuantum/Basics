// Aus einer 2byte-Binärzahl einen base-36 Seriennummernstring machen
char *wordtoserno(word Binaer) {
 char SerNStr[4];
 static char Seriennummer[4];
 int i,l;
  // limitation
  if (Binaer > 46655L)
    Binaer = 46655L;
  ltoa(Binaer,SerNStr,36);
  sprintf(Seriennummer,"%3s",SerNStr);
  strupr(Seriennummer);
  // generate leading zeroes
  l = strlen(Seriennummer);
  for (i=0; i<l; i++) {
    if (Seriennummer[i] == ' ')
      Seriennummer[i] = '0';
  };
  return Seriennummer;
}