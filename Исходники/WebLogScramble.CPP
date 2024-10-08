U0 LogScrambleFile(U8 *name)
{
  CDoc *doc=DocRead(name,DOCF_PLAIN_TEXT);
  CDocEntry *doc_e=doc->root.next;
  I64 i;
  U32 num;
  U8 *st,*st2;
  "Scrambling:%s\n",name;
  while (doc_e!=doc) {
    if (doc_e->type_u8==DOCT_TEXT) {
      st=MAlloc(StrLen(doc_e->tag)+1);
      st2=MAlloc(StrLen(doc_e->tag)+1);
      StrFirstRem(doc_e->tag," ",st);

      for (i=3;i>=0;i--) {
	StrFirstRem(st,".",st2);
	num.u8[i]=key[i][A2I(st2)&255];
      }
 
      Free(st);
      Free(st2);

      st=MSPrintF("%d.%d.%d.%d %s",num.u8[3],num.u8[2],num.u8[1],num.u8[0],doc_e->tag);
      Free(doc_e->tag);
      doc_e->tag=st;
    }
    doc_e=doc_e->next;
  }
  DocWrite(doc);
  DocDel(doc);
}