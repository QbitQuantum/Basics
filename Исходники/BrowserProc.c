static
unsigned long ChildNumberbyChar(struct Instance *i, char *name)
{
  struct InstanceName rec;
  symchar *sym;
  unsigned long c = 0;
  unsigned long nch = 0;
  long iindex;

  if((!i)||(!name)) {
    FPRINTF(ASCERR,"Null Instance or name in ChildbyNameChar\n");
    FFLUSH(ASCERR);
    return 0;
  }
  nch = NumberChildren(i);
  sym = AddSymbol(name);
  if(!nch) {
    return 0;
  }
  do {
    c++;
    rec = ChildName(i,c);
    switch (InstanceNameType(rec)) {
    case StrName:
      if (CmpSymchar(InstanceNameStr(rec), sym)==0) {
        return c;
      }
      break;
    case IntArrayIndex:
      iindex = atol(name); /* fixme strtod */
      if (iindex==InstanceIntIndex(rec)) {
        return c;
      }
      break;
    case StrArrayIndex:
      if (CmpSymchar(InstanceStrIndex(rec), sym)==0) {
        return c;
      }
      break;
    }
  } while(c < nch);
  return 0; /*NOTREACHED*/
}