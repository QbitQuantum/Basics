static int jtWrite(
  sqlite3_file *pFile, 
  const void *zBuf, 
  int iAmt, 
  sqlite_int64 iOfst
){
  int rc;
  jt_file *p = (jt_file *)pFile;
  if( p->flags&SQLITE_OPEN_MAIN_JOURNAL ){
    if( iOfst==0 ){
      jt_file *pMain = locateDatabaseHandle(p->zName);
      assert( pMain );
  
      if( iAmt==28 ){
        closeTransaction(pMain);
      }else if( iAmt!=12 ){
        u8 *z = (u8 *)zBuf;
        pMain->nPage = decodeUint32(&z[16]);
        pMain->nPagesize = decodeUint32(&z[24]);
        if( SQLITE_OK!=(rc=openTransaction(pMain, p)) ){
          return rc;
        }
      }
    }
    if( p->iMaxOff<(iOfst + iAmt) ){
      p->iMaxOff = iOfst + iAmt;
    }
  }

  if( p->flags&SQLITE_OPEN_MAIN_DB && p->pWritable ){
    if( iAmt<p->nPagesize 
     && p->nPagesize%iAmt==0 
     && iOfst>=(PENDING_BYTE+512) 
     && iOfst+iAmt<=PENDING_BYTE+p->nPagesize
    ){
    }else{
      u32 pgno = iOfst/p->nPagesize + 1;
      assert( (iAmt==1||iAmt==p->nPagesize) && ((iOfst+iAmt)%p->nPagesize)==0 );
      assert( pgno<=p->nPage || p->nSync>0 );
      assert( pgno>p->nPage || sqlite3BitvecTest(p->pWritable, pgno) );
    }
  }

  rc = sqlite3OsWrite(p->pReal, zBuf, iAmt, iOfst);
  if( (p->flags&SQLITE_OPEN_MAIN_JOURNAL) && iAmt==12 ){
    jt_file *pMain = locateDatabaseHandle(p->zName);
    int rc2 = readJournalFile(p, pMain);
    if( rc==SQLITE_OK ) rc = rc2;
  }
  return rc;
}