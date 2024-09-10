void Nuc3ptStru::PrintTheTag(FILE *fp)
{
  G.printTag(fp);
  Fprintf(fp,"_") ;
  D.printTag(fp) ;
  if(strlen(tag)>0) Fprintf(fp,"_%s",tag) ;
} 