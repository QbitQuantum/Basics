void list_symbol()
{
  unsigned int i=0;
  char debug__[80];

  i = 0;
  while(tab_import_symb[i].address && (i<MAX_SYMBOL))
    {
      Sprintf(debug__, "%s %.8X", tab_import_symb[i].name, tab_import_symb[i].address);
      insertinbuffer(debug__);     
      i++;
    }
  
}