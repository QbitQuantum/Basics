static char read_set(FILE *txt,char *var,char *set)
  {
  int c;
  char *cc;

  fscanf(txt,"%[^=]%c",var,&c);
  do
     c = fgetc(txt);
  while (c<33);
  if (c =='"') fscanf(txt,"%[^\"]%c%c",set,&c,&c);
  else if (c =='\'') fscanf(txt,"%[^']%c%c",set,&c,&c);
  else
     {
     ungetc(c,txt);
     fscanf(txt,"%[^> ]%c",set,&c);
     }
  while(c<33 && c != EOF) c = fgetc(txt);
  if (c !='>') ungetc(c,txt);
  cc = strchr(var,0);
  while (cc != var)
     {
     cc--;
     if (*cc>32)
        {
        cc++;
        break;
        }
     }
  *cc = 0;
  _strupr(set);
  _strupr(var);
  return c;
  }