char* MYRTLEXP HDBValue2Str( PHDBValue p,char *Buff, int bSz )
  {  DWORD n;
     int   len;

     Buff[0] = 0;
     switch( p->Type ) {
       case HDB_TP_DATETIME: SNprintf( Buff, bSz,
                                       "%02d-%02d-%04d %02d:%02d:%02d",
                                       p->Value.vDateTime->mon, p->Value.vDateTime->mday, p->Value.vDateTime->year,
                                       p->Value.vDateTime->hour, p->Value.vDateTime->min, p->Value.vDateTime->sec );
                          break;
       case     HDB_TP_DATE: SNprintf( Buff, bSz,
                                       "%02d-%02d-%04d",
                                       p->Value.vDate->mon, p->Value.vDate->mday, p->Value.vDate->year );
                          break;
       case     HDB_TP_TIME: SNprintf( Buff, bSz,
                                       "%02d:%02d:%02d",
                                       p->Value.vTime->hour, p->Value.vTime->min, p->Value.vTime->sec );
                          break;
       case   HDB_TP_STRING: SNprintf( Buff, bSz, "\"%s\"", p->Value.vString );
                          break;
       case     HDB_TP_WORD: SNprintf( Buff, bSz, "%5d", *p->Value.vWord );
                          break;
       case    HDB_TP_DWORD: SNprintf( Buff, bSz, "%08X", *p->Value.vDword );
                          break;
       case   HDB_TP_DOUBLE: SNprintf( Buff, bSz, "%3.3lf", *p->Value.vDouble );
                          break;
       case   HDB_TP_BINARY: len = SNprintf( Buff, bSz, "%d:", p->Size );
                             for( bSz -= 2,n = 0; len < bSz && n < p->Size; len += 2, n++ )
                               Sprintf( Buff+len, "%02X", ((LPBYTE)p->Value.Data)[n] );
                          break;
     }

 return Buff;
}