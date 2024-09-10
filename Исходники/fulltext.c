/* Delete a row from the full-text index. */
static int index_delete(fulltext_vtab *v, sqlite_int64 iRow){
  char *zText;
  Hash terms;
  HashElem *e;

  int rc = content_select(v, iRow, &zText);
  if( rc!=SQLITE_OK ) return rc;

  rc = build_terms(&terms, v->pTokenizer, zText, iRow);
  free(zText);
  if( rc!=SQLITE_OK ) return rc;

  for(e=HashFirst(&terms); e; e=HashNext(e)){
    rc = index_delete_term(v, HashKey(e), HashKeysize(e), iRow);
    if( rc!=SQLITE_OK ) break;
  }
  for(e=HashFirst(&terms); e; e=HashNext(e)){
    DocList *p = HashData(e);
    docListDelete(p);
  }
  HashClear(&terms);

  return content_delete(v, iRow);
}