static BOOL DDESendMess(CHAR *lpBuffer)
{
 CHAR szService[] = DDEDBG_APPNAME ;
 CHAR szTopic[] = DDEDBG_TOPIC;
 HSZ  hszService, hszTopic, hszItem ;
 HCONV hConv ;
 HDDEDATA hde;
 SINT i;

#ifdef LOG
LOGWrite("DDE","DDE:sm [%s]",lpBuffer);
#endif
 if (idInst==0)
 {
  if (DdeInitialize (&idInst, (PFNCALLBACK) &DdeCallback, APPCLASS_STANDARD | APPCMD_CLIENTONLY, 0L))
     {
#ifdef LOG
		LOGWrite("DDE","Non inizializzo");
#endif
		return FALSE;
     }
 }

#ifdef LOG
 LOGWrite("DDE","DDE:sm 1 [%s]",lpBuffer);
#endif
 // Try connecting

 hszService = DdeCreateStringHandle (idInst , szService, 0) ;
 hszTopic   = DdeCreateStringHandle (idInst , szTopic,   0) ;

 hConv = DdeConnect (idInst , hszService, hszTopic, NULL) ;

#ifdef LOG
 if (hConv==NULL) LOGWrite("DDE","Non trovo il server");
#endif
 // Se non c'è il server lo attivo
/*
 if (hConv == NULL)
 {
  WinExec ("c:\\eh3\\develop\\ddedbg.exe", SW_NORMAL) ;
  hConv = DdeConnect (idInst, hszService, hszTopic, NULL) ;
 }
*/
#ifdef LOG
LOGWrite("DDE","DDE:sm 2 [%s]",lpBuffer);
#endif
 // Free the string handles
 DdeFreeStringHandle (idInst , hszService) ;
 DdeFreeStringHandle (idInst , hszTopic) ;

#ifdef LOG
 LOGWrite("DDE","DDE:sm 3 [%s]",lpBuffer);
#endif
 // If still not connected, display message box
if (hConv == NULL)
{
	dispx("DDDebug.server non presente."); 
	return FALSE;
 }

#ifdef LOG
 LOGWrite("DDE","DDE:sm 4 [%s]",lpBuffer);
#endif
 hszItem = DdeCreateStringHandle (idInst , lpBuffer, 0) ;

 for (i=0;i<30;i++)
 {
//  hde=DdeClientTransaction (NULL, 0, hConv, hszItem, CF_TEXT,XTYP_ADVSTART | XTYPF_ACKREQ,DDE_TIMEOUT, NULL) ;
  hde=DdeClientTransaction (lpBuffer, strlen(lpBuffer)+1, hConv, 0L, CF_TEXT,XTYP_EXECUTE,DDE_TIMEOUT, NULL) ;
#ifdef LOG
  if (hde==0)
  {
	LOGWrite("DDE","Error=%d",DdeGetLastError(idInst));	 
  }
  else 
#endif
  break;
 }
//DMLERR_LOW_MEMORY
 
 DdeFreeStringHandle (idInst , hszItem) ;
 return TRUE;
}