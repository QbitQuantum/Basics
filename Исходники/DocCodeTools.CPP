U0 EdRenumAsm(CDoc *doc)
{
  Bool unlock=DocLock(doc);
  I64 num=0;
  CRenum root,*tempr,*tempr1;
  U8 buf[sizeof(CEdFindText.find_text)],
	buf2[sizeof(CEdFindText.find_text)];

  QueInit(&root);
  EdSelectFun(doc,TRUE);
  EdRACollect(doc,&root);

  tempr=root.next;
  while (tempr!=&root) {
    tempr1=tempr->next;
    num+=ASM_RENUM_SPACING;
    SPrintF(buf,"@#%02d",num);
    EdReplace(doc,tempr->label,buf,TRUE,TRUE,TRUE);
    Free(tempr);
    tempr=tempr1;
  }

  while (num) {
    SPrintF(buf, "@#%02d",num);
    SPrintF(buf2,"@@%02d",num);
    EdReplace(doc,buf,buf2,TRUE,TRUE,TRUE);
    num-=ASM_RENUM_SPACING;
  }
  EdSelectAll(doc,FALSE);
  DocRecalc(doc);
  DocCenter(doc);
  if (unlock)
    DocUnlock(doc);
}