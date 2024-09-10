public Bool DocTreeFind(CDoc *doc,U8 *path,
  CDocEntry **_tree_entry=NULL,
  CDocEntry **_start_indent=NULL, CDocEntry **_end_indent=NULL)
{
  I64 i=0,k=0;
  U8 *st1=StrNew(path),*st2=MAlloc(StrLen(path)+1);
  Bool result=FALSE,unlock_doc=DocLock(doc);
  CDocEntry *doc_e=doc->root.next;
  if (_tree_entry) *_tree_entry=doc;
  if (_start_indent) *_start_indent=doc;
  if (_end_indent) *_end_indent=doc;
  while (*st1 && doc_e!=doc) {
    StrFirstRem(st1,"/",st2);
    if (*st2) {
      while (doc_e!=doc) {
	if (doc_e->type_u8==DOCT_INDENT)
	  i+=doc_e->attr;
	else if (i==k && doc_e->flags1&DOCEF1_TREE && !StrCmp(doc_e->tag+3,st2)) {
	   if (*st1)
	     break;
	   else {
	     if (_tree_entry) *_tree_entry=doc_e;
	     i=0;
	     while (doc_e!=doc && doc_e->type_u8!=DOCT_INDENT)
	       doc_e=doc_e->next;
	     if (doc_e!=doc) {
	       i=doc_e->attr;
	       if (_start_indent) *_start_indent=doc_e;
	       doc_e=doc_e->next;
	       while (doc_e!=doc && i>0) {
		 if (doc_e->type_u8==DOCT_INDENT) {
		   i+=doc_e->attr;
		   if (i<=0) {
		     if (_end_indent) *_end_indent=doc_e;
		     result=TRUE;
		     break;
		   }
		 }
		 doc_e=doc_e->next;
	       }
	     }
	     goto ft_done;
	   }
	}
	doc_e=doc_e->next;
      }
      k+=2;
    }
  }
ft_done:
  if (unlock_doc)
    DocUnlock(doc);
  Free(st1);
  Free(st2);
  return result;
}