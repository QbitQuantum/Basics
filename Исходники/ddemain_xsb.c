HDDEDATA FAR PASCAL _export DdeCallback(UINT type, UINT fmt,
                        HCONV hConv, HSZ hsz1, HSZ hsz2,
                        HDDEDATA data, DWORD data1,
                        DWORD data2)
{
  long int ind, i, spaceneeded, sizeQuery;
  DWORD Qlen, QSegLen;
  static HCONV handConv;
  static HDDEDATA hdDataHandle;

    /*DdeQueryString(idInst,hsz1,szBuff1,sizeof(szBuff1),0);
    DdeQueryString(idInst,hsz2,szBuff2,sizeof(szBuff2),0);
    
    fprintf(stderr,"DDE Callback, type=%d, fmt=%d, hConv=%d, hsz1=%s, hsz2=%s,\n d1=%x, d2=%x\n",
        type,fmt,hConv,szBuff1,szBuff2,data1,data2);*/

    
    switch (type) {
      case XTYP_ERROR:
        fprintf(stderr,"error: xtyp_error\n");
        return NULL;
      case XTYP_ADVDATA:
        fprintf(stderr,"DDE msg received ADVDATA\n");
        return DDE_FNOTPROCESSED;
      case XTYP_ADVREQ:
        fprintf(stderr,"DDE msg received ADVREQ\n");
        return NULL;
      case XTYP_ADVSTART:
        fprintf(stderr,"DDE msg received ADVSTART\n");
        return NULL;
      case XTYP_ADVSTOP:
        fprintf(stderr,"DDE msg received ADVSTOP\n");
        return NULL;
      
      case XTYP_CONNECT:
        DdeQueryString(idInst,hsz2,szBuffer,sizeof(szBuffer),0);
        if (strcmp(szBuffer,szAppName)) return FALSE;
        Qlen = DdeQueryString(idInst,hsz1,NULL,0,0);
        szQuery = (char *)malloc(Qlen+1);
        (void)DdeQueryString(idInst,hsz1,szQuery,Qlen+1,0);
        if (!strcmp(szQuery,"XSB")) {
            free(szQuery);
            szQuery = NULL;
        }
        return TRUE;

      case XTYP_CONNECT_CONFIRM:
        handConv = hConv;
        return TRUE;

      case XTYP_DISCONNECT:
        return NULL;
      case XTYP_EXECUTE:
        fprintf(stderr,"DDE msg received EXECUTE\n");
        return DDE_FNOTPROCESSED;

      case XTYP_POKE:
        QSegLen = DdeGetData(data,NULL,100000,0L);
        if (!szQuery) {
            szQuery = (char *)malloc(QSegLen);
            QSegLen = DdeGetData(data,szQuery,100000,0L);
            sizeQuery = QSegLen;
        } else {
            szQuery = (char *)realloc(szQuery,sizeQuery+QSegLen+1);
            QSegLen = DdeGetData(data,szQuery+sizeQuery,100000,0L);
            sizeQuery =+ QSegLen;
        }
        return DDE_FACK;
        
      case XTYP_REGISTER:
        fprintf(stderr,"DDE msg received REGISTER\n");
        return NULL;

      case XTYP_REQUEST:
        /*fprintf(stderr,"DDE msg received REQUEST:\n");*/
        if (!szQuery) return NULL;
        if (sizeBuff3 < 10) {
            szBuff3 = (char *)malloc(initsizeBuff3);
            sizeBuff3 = initsizeBuff3;
        }
        ind = 0;
        rcode = xsb_query_string(szQuery);      /* call the query */
        if (rcode) {
            strcpy(szBuff3+ind,"no\r");
            ind += 3;
        } else if (is_string(reg_term(2)) || p2c_arity(reg_term(2))==0) {
            strcpy(szBuff3+ind,"yes\r");
            ind += 4;
            while (!rcode) rcode = xsb_next();
        } else while (!rcode) {
            spaceneeded = ind + clenpterm(reg_term(2)) + 20;  /* fudge factor */
            if (spaceneeded > sizeBuff3) {
                while (spaceneeded > sizeBuff3) {sizeBuff3 = 2*sizeBuff3;}
                szBuff3 = realloc(szBuff3,sizeBuff3);
            }
            for (i=1; i<p2c_arity(reg_term(2)); i++) {
                printpterm(p2p_arg(reg_term(2),i),TRUE,szBuff3,&ind);
                strcpy(szBuff3+ind,"\t");
                ind += 1;
            }
            printpterm(p2p_arg(reg_term(2),p2c_arity(reg_term(2))),TRUE,szBuff3,&ind);
            strcpy(szBuff3+ind,"\r");
            ind += 1;
            rcode = xsb_next();
        }
        hdDataHandle = DdeCreateDataHandle(idInst,szBuff3,ind+1,0,hsz2,CF_TEXT,0);
        free(szQuery);
        szQuery = NULL;
        return hdDataHandle;

      case XTYP_WILDCONNECT:
        fprintf(stderr,"DDE msg received WILDCONNECT\n");
        return NULL;
      default:
        fprintf(stderr,"DDE msg received: %d\n",type);        
    }
    return NULL;
}