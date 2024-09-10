/*
** Write a full decode on stdout for the cell at a[ofst].
** Assume the page contains a header of size szPgHdr bytes.
*/
static void decodeCell(
  unsigned char *a,       /* Page content (without the page-1 header) */
  unsigned pgno,          /* Page number */
  int iCell,              /* Cell index */
  int szPgHdr,            /* Size of the page header.  0 or 100 */
  int ofst                /* Cell begins at a[ofst] */
){
  int i, j = 0;
  int leftChild;
  i64 k;
  i64 nPayload;
  i64 rowid;
  i64 nHdr;
  i64 iType;
  i64 nLocal;
  unsigned char *x = a + ofst;
  unsigned char *end;
  unsigned char cType = a[0];
  int nCol = 0;
  int szCol[2000];
  int ofstCol[2000];
  int typeCol[2000];

  printf("Cell[%d]:\n", iCell);
  if( cType<=5 ){
    leftChild = ((x[0]*256 + x[1])*256 + x[2])*256 + x[3];
    printBytes(a, x, 4);
    printf("left child page:: %d\n", leftChild);
    x += 4;
  }
  if( cType!=5 ){
    i = decodeVarint(x, &nPayload);
    printBytes(a, x, i);
    nLocal = localPayload(nPayload, cType);
    if( nLocal==nPayload ){
      printf("payload-size: %lld\n", nPayload);
    }else{
      printf("payload-size: %lld (%lld local, %lld overflow)\n",
             nPayload, nLocal, nPayload-nLocal);
    }
    x += i;
  }else{
    nPayload = nLocal = 0;
  }
  end = x + nLocal;
  if( cType==5 || cType==13 ){
    i = decodeVarint(x, &rowid);
    printBytes(a, x, i);
    printf("rowid: %lld\n", rowid);
    x += i;
  }
  if( nLocal>0 ){
    i = decodeVarint(x, &nHdr);
    printBytes(a, x, i);
    printf("record-header-size: %d\n", (int)nHdr);
    j = i;
    nCol = 0;
    k = nHdr;
    while( x+j<end && j<nHdr ){
       const char *zTypeName;
       int sz = 0;
       char zNm[30];
       i = decodeVarint(x+j, &iType);
       printBytes(a, x+j, i);
       printf("typecode[%d]: %d - ", nCol, (int)iType);
       switch( iType ){
         case 0:  zTypeName = "NULL";    sz = 0;  break;
         case 1:  zTypeName = "int8";    sz = 1;  break;
         case 2:  zTypeName = "int16";   sz = 2;  break;
         case 3:  zTypeName = "int24";   sz = 3;  break;
         case 4:  zTypeName = "int32";   sz = 4;  break;
         case 5:  zTypeName = "int48";   sz = 6;  break;
         case 6:  zTypeName = "int64";   sz = 8;  break;
         case 7:  zTypeName = "double";  sz = 8;  break;
         case 8:  zTypeName = "zero";    sz = 0;  break;
         case 9:  zTypeName = "one";     sz = 0;  break;
         case 10:
         case 11: zTypeName = "error";   sz = 0;  break;
         default: {
           sz = (int)(iType-12)/2;
           sprintf(zNm, (iType&1)==0 ? "blob(%d)" : "text(%d)", sz);
           zTypeName = zNm;
           break;
         }
       }
       printf("%s\n", zTypeName);
       szCol[nCol] = sz;
       ofstCol[nCol] = (int)k;
       typeCol[nCol] = (int)iType;
       k += sz;
       nCol++;
       j += i;
    }
    for(i=0; i<nCol && ofstCol[i]+szCol[i]<=nLocal; i++){
       int s = ofstCol[i];
       i64 v;
       const unsigned char *pData;
       if( szCol[i]==0 ) continue;
       printBytes(a, x+s, szCol[i]);
       printf("data[%d]: ", i);
       pData = x+s;
       if( typeCol[i]<=7 ){
         v = (signed char)pData[0];
         for(k=1; k<szCol[i]; k++){
           v = (v<<8) + pData[k];
         }
         if( typeCol[i]==7 ){
           double r;
           memcpy(&r, &v, sizeof(r));
           printf("%#g\n", r);
         }else{
           printf("%lld\n", v);
         }
       }else{
         int ii, jj;
         char zConst[32];
         if( (typeCol[i]&1)==0 ){
           zConst[0] = 'x';
           zConst[1] = '\'';
           for(ii=2, jj=0; jj<szCol[i] && ii<24; jj++, ii+=2){
             sprintf(zConst+ii, "%02x", pData[jj]);
           }
         }else{
           zConst[0] = '\'';
           for(ii=1, jj=0; jj<szCol[i] && ii<24; jj++, ii++){
             zConst[ii] = ISPRINT(pData[jj]) ? pData[jj] : '.';
           }
           zConst[ii] = 0;
         }
         if( jj<szCol[i] ){
           memcpy(zConst+ii, "...'", 5);
         }else{
           memcpy(zConst+ii, "'", 2);
         }
         printf("%s\n", zConst);
       }
       j = ofstCol[i] + szCol[i];
    }
  }
  if( j<nLocal ){
    printBytes(a, x+j, 0);
    printf("... %lld bytes of content ...\n", nLocal-j);
  }
  if( nLocal<nPayload ){
    printBytes(a, x+nLocal, 4);
    printf("overflow-page: %d\n", decodeInt32(x+nLocal));
  }
}