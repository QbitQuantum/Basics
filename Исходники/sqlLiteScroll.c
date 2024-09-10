//
// Driver Odbc
//
void *	sqlLiteScroll(struct OBJ *objCalled,EN_MESSAGE cmd,LONG info,CHAR *str)
{
	static struct WINSCR rit,*PtScr;
	EH_DISPEXT *psExt;
	
    S_SCR_INFO * psSI,sSqlInfo;
	INT   a;//,b;
//	INT   ptClient;
//	SQLRETURN sqlReturn;

	//
	// Inizializzazione
	//
	if (_local.bReset)
	{
		_local.lstScr=lstCreate(sizeof(S_SCR_INFO));
		 FTIME_on(_SqlThreadRefresh,1);
		_local.bReset=false;
	}

	// Oggetto buono ?
	if ((objCalled->tipo!=OW_SCR)&&(objCalled->tipo!=OW_SCRDB)) return 0;

	psSI=objCalled->pOther;
	if (cmd==WS_INF) return &psSI->ws;

	switch (cmd) 
	{
	// -----------------------------------
	// APERTURA DEL DRIVER               |
	// -----------------------------------

		case WS_CREATE: //break;

#ifdef OS_DEBUG
			printf("OdbcScroll: Create" CRLF);
#endif

			_(sSqlInfo);
			objCalled->pOther=lstPush(_local.lstScr,&sSqlInfo);
			psSI=objCalled->pOther;
			psSI->ObjClient=objCalled;
			psSI->ObjClient->bFreeze=TRUE; // Blocco la gestione dell'oggetto
			psSI->bDrawLineDiv=TRUE;
#ifdef EH_SQL_SQLITE
			psSI->enPlatform=_SQL_SQLITE;
#endif
#ifdef EH_SQL_MYSQL
			psSI->enPlatform=_SQL_MYSQL;
#endif

			//
			// Alla prima chiamata creo thread e "finestrame" necessario 
			// 

			// Tecnologia sqlLite
			//		- La connessione deve essere inizializzata
			//
			if (!psSI->hThread)
			{
				memset(&psSI->csSqdStruct,0,sizeof(CRITICAL_SECTION));
				memset(&psSI->csSqdQuery,0,sizeof(CRITICAL_SECTION));
				InitializeCriticalSection(&psSI->csSqdStruct); 
				InitializeCriticalSection(&psSI->csSqdQuery); 
/*
			
				// 
				// Alloco lo stantment clone ( Si libererà con WS_DESTROY)
				//
				sqlReturn=SQLAllocHandle(SQL_HANDLE_STMT, sOdbcSection.hConn, &psSI->hStmtScroll);
				if (sqlReturn!=SQL_SUCCESS&&sqlReturn!=SQL_SUCCESS_WITH_INFO) ehExit("OdbcScroll:hStmt Clone impossible %d",sqlReturn);

				// Bho ?
				SQLSetStmtAttr(psSI->hStmtScroll, SQL_ATTR_CONCURRENCY, (SQLPOINTER) SQL_CONCUR_READ_ONLY, 0);

				sqlReturn=SQLSetStmtAttr(psSI->hStmtScroll, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER) SQL_SCROLLABLE , 0);
				if (sqlReturn==SQL_ERROR)  
				// Altro metodo
				{
					sqlReturn=SQLSetStmtAttr( psSI->hStmtScroll,SQL_ATTR_CURSOR_TYPE,  (SQLPOINTER) SQL_CURSOR_STATIC, 0);
					if (sqlReturn==SQL_ERROR) win_infoarg("errore in assegnazione cursore");
					sqlReturn=SQLSetStmtAttr( psSI->hStmtScroll, SQL_ATTR_USE_BOOKMARKS, (SQLPOINTER) SQL_UB_VARIABLE, 0);
					if (sqlReturn==SQL_ERROR) win_infoarg("SQL_ATTR_USE_BOOKMARKS");
				}

				//sprintf(szCursor,"SQD%d",ptClient);
				//SQLTRY(SQL_HANDLE_STMT,"SQD->",psSI->hStmtScroll,SQLSetCursorName(psSI->hStmtScroll, szCursor, SQL_NTS));
				//SQLTRY("ASYNC",psSI->hStmtScroll,SQLSetStmtAttr(psSI->hStmtScroll, SQL_ATTR_ASYNC_ENABLE, (SQLPOINTER) SQL_ASYNC_ENABLE_ON , 0));


				//
				// 4) Creo il Thread (SQLExecuteThread) per l'elaborazione delle query
				//
				*/
				for (a=0;a<ESQL_MAXEVENTLOAD;a++) psSI->arhEvent[a]=CreateEvent(NULL,true,FALSE,NULL); 
				psSI->hThread = CreateThread(NULL, 
											  0, 
											  _sqlExecuteThread, 
											  (LPDWORD) psSI,
											  0, 
											  &psSI->dwThread);
				psSI->bAutoRowSelect=TRUE; // <-- 2010 - Inserito auto select in partenza
				SetThreadPriority(psSI->hThread,THREAD_PRIORITY_NORMAL);
			}
			break;

		case WS_OPEN:

		//
		//	Inizializzazione della finestra
		//	
			if (info<3) {ehExit("Field ? " __FUNCTION__);}
			psSI->ws.numcam=info;// Assegna il numero di campi da visualizzare
			psSI->ws.selez=-1; 
			psSI->ws.maxcam=0;
			psSI->ObjClient->tipo=OW_SCR;
			psSI->lRowsTotal=0;
			psSI->fChanged=0;
			psSI->ObjClient->bFreeze=FALSE;

			if (psSI->funcNotify) psSI->funcNotify(_adaptor(objCalled,WS_OPEN,0,NULL,NULL));//objCalled,NULL,0,NULL,WS_OPEN,NULL,NULL);
			psSI->ws.bExtSelection=TRUE; // Gestione esterna della selezione
			psSI->ws.fNoBlankLine=TRUE;
			

		case WS_LOAD:  
			break;

	// -----------------------------------
	// Richiesta di refresh
	// -----------------------------------
	case WS_RELOAD: 
			if (info)
				_queryExecute(psSI,__LINE__); 
				else
				_fetch(psSI); 
				
			return NULL; // Non serve stampare

	// -----------------------------------
	// WS_CLOSE IL DRIVER                  |
	// -----------------------------------
	case WS_CLOSE:
			sqlLiteScroll(objCalled,WS_PROCESS,STOP,NULL); // Chiedo di fermare il processo in corso
			psSI->ObjClient->bFreeze=true;
			if (psSI->funcNotify) (psSI->funcNotify)(_adaptor(objCalled,WS_CLOSE,0,NULL,NULL));
			break;

	// -----------------------------------
	// CHIUSURA DEFINITIVA DEL GESTORE (chiamato in obj_close());
	// -----------------------------------
	case WS_DESTROY: 

			//
			// Notifico la chiusura alla funzione esterna
			//
			if (psSI->funcNotify) (psSI->funcNotify)(_adaptor(objCalled,WS_DESTROY,0,NULL,NULL));

			// Fermo il Thread
			SetEvent(psSI->arhEvent[ESQL_STOP]); // Segnalo che siamo in chiusura
			if (WaitForSingleObject(psSI->hThread,5000)) 
			 {
				//_dx_(0,20,"Entro qui");
				//SQLFetchScroll(psSI->hStmtScroll,SQL_FETCH_FIRST,0);
				//SQLFreeHandle(SQL_HANDLE_STMT,psSI->hStmtScroll); psSI->hStmtScroll=0;
				//_dx_(0,40,"Terminate %d",TerminateThread(psSI->hThread,0));
			 }

			/*
			 if (psSI->hStmtScroll) {SQLFreeHandle(SQL_HANDLE_STMT,psSI->hStmtScroll); psSI->hStmtScroll=0;}
			 if (psSI->rsSet) {odbc_QueryResultDestroy(psSI->rsSet); ehFree(psSI->rsSet);}
			 psSI->rsSet=NULL;

			 // Libero la memoria usata per la Query
			 ehFreePtr(&psSI->pQueryActive);
			 ehFreePtr(&psSI->pszQueryCount);
			 ehFreePtr(&psSI->pLastErrorText);

			 // Libero la memoria usata per la WhereAdd
			 ehFreePtr(&psSI->pQuerySelect);

			 ehFreePtr(&psSI->pszKeyCode);
			 ARDestroy(psSI->arKeyCodeFld);
			 ehFreePtr(&psSI->pCodeFocused);
			 ehFreePtr(&psSI->pCodeSelected);
			 ehFreePtr(&psSI->pCodeReturn);

			 // Libero gli Handle degli eventi
			 for (a=0;a<ESQL_MAXEVENTLOAD;a++) CloseHandle(psSI->arhEvent[a]);

			 // 1.2.3. Liberi tutti !!
			 DeleteCriticalSection(&psSI->csSqdStruct); 
			 DeleteCriticalSection(&psSI->csSqdQuery); 
			 // Azzero la struttura di riferimento
			 memset(psSI,0,sizeof(S_SCR_INFO));
			 */
			{
				EH_LST_I * psi;
				psi=lstSearch(_local.lstScr,objCalled->pOther);
				lstRemoveI(_local.lstScr,psi);
			}
			 ehFreePtr(&objCalled->pOther);
			 break;

	// -----------------------------------
	// PRESSIONE DI UN TASTO/MOUSE       |
	// -----------------------------------
	case WS_KEYPRESS:
			if (key_press2(KEY_F9)) {strcpy(str,"ESC:F9"); break;}
			if (psSI->funcNotify) (psSI->funcNotify)(_adaptor(objCalled,cmd,info,str,NULL)); 
			break;

	// -----------------------------------
	// SETTA SELEZIONE RECORD            |
	// -----------------------------------
	case WS_SEL: 
			if (!psSI->funcNotify) break;//ehExit(SdbDriver32 ":No ext/disp function");
			// if (!psSI->rsSet) break;
			// printf("%d",psSI->rsSet->iCurrentRow);
			//if (psSI->ws.selez==-1) break;
			break;

	// -------------------------------------
	// SETTA L'OFFSET  (Solo Modo O_SCROLL |
	// -------------------------------------
	case WS_OFF: break;

	// -------------------------------------
	// 
	// -------------------------------------
	case WS_PTREC : //			  			Restituisce pt alla chiave selezionata
	case WS_GET_SELECTED:

			_(rit);
			rit.record=-1;

			if (strEmpty(psSI->pszKeyCode)) {efx2(); return NULL;}
			/*
			//
			// Selezione in scroll
			//
			if (psSI->rsSet&&psSI->ws.selez>-1)
			{
				psSI->rsSet->iCurrentRow=psSI->ws.selez;
				if (strEmpty(psSI->pszKeyCode)) ehExit("%s:%d manca assegnazione pszKeyCode",__FILE__,__LINE__);
				_keyCodeBuilder(&psSI->pCodeReturn,psSI);

				rit.record=psSI->ws.selez;
				rit.keypt=psSI->pCodeReturn;
				if (psSI->bAutoRowSelect)
				{
					strAssign(&psSI->pCodeSelected,psSI->pCodeReturn);
					InvalidateRect(objCalled->hWnd,NULL,FALSE);
				}
			}
			//
			// Pre-selezione (non entrao in scroll
			//
			else if (!strEmpty(psSI->pCodeSelected)) {

				rit.record=psSI->ws.selez;
				rit.keypt=psSI->pCodeSelected;
			}
			if (cmd==WS_GET_SELECTED) return retCreate(_ALFA,rit.record,rit.keypt);
			*/
			return &rit;

	// -------------------------------------
	// RITORNA Selez ??????????            |
	// -------------------------------------
	case WS_REALGET:
			 break;

	// -------------------------------------
	// Refresh a ON                        |
	// -------------------------------------
	case WS_REFON : psSI->ws.refre=ON; break;
	case WS_REFOFF : psSI->ws.refre=OFF; break;

	case WS_PROCESS:
		if (info==STOP&&!str)
		 {
			// SQLCancel(psSI->hStmtScroll); // Cancello il processo nello stantment
			 printf("> cancellare processo in corso");
			EnterCriticalSection(&psSI->csSqdStruct);
			psSI->fBreak=true;
			LeaveCriticalSection(&psSI->csSqdStruct);
			while (TRUE) {if (!psSI->fInProcess) break; else Sleep(50);}
			//win_infoarg("SQL stop");
		}
		// Controllo se l'elaborazione è in corso
		if ((info==0)&&(*str=='?'))
		{
		  if (psSI->fInProcess) return "!"; else return NULL;
		}
		break;

	
	// 
	// Chiedo di cambiare il la Where di ricerca
	//
	case WS_SETFILTER:

		EnterCriticalSection(&psSI->csSqdStruct);
		ehFreePtr(&psSI->pQuerySelect); 
	 	psSI->pQuerySelect=strDup(str);
		psSI->ws.selez=-1;
		psSI->ws.maxcam=0;
		psSI->lRowsReady=0;
		psSI->lRowsTotal=0;
		LeaveCriticalSection(&psSI->csSqdStruct);
		if (info)
		{
			InvalidateRect(objCalled->hWnd,NULL,TRUE);
			_message(psSI,TRUE,"Attendere\nRichiesta al server ...");
			OsEventLoop(5);
		}
		psSI->fQueryToExecute=true;
		// _queryExecute(psSI,__LINE__); // Me ne arriva uno dopo
		break;

	case WS_SETFLAG:
		objCalled->pOtherEx=str; // Assegno un puntatore esterno
		if (psSI->funcNotify) (psSI->funcNotify)(_adaptor(objCalled,WS_SETFLAG,info,NULL,NULL)); 
		break;

	// -------------------------------------
	// Richiesta di Stampa dei Dati        |
	// -------------------------------------
	case WS_DISPLAY : //			  			Richiesta buffer
			 
			psExt=(EH_DISPEXT *) str;

			if (!psSI->funcNotify) {
				Tboxp(	psExt->rClientArea.left,
						psExt->rClientArea.top,
						psExt->rClientArea.right,
						psExt->rClientArea.bottom-1,
						RGB(255,128,0),SET);
//						arError=ARCreate(psSI->pLastErrorText,"\n",&iRow);
				dispf(psExt->px+1,psExt->py+1,RGB(255,255,255),-1,STYLE_NORMAL,"SMALL F",3,"-Not func for Display-");
				break;
			}

			//
			// Richiesta di stampa del titolo
			//
			if (psExt->ncam==-10) 
			{
				psSI->funcNotify(_adaptor(objCalled,WS_DISPLAY,0,psExt,NULL));//psSI->Hdb,psSI->iIndex); 
				break;
			}
/*
			if (!psSI->rsSet) 
			{
				if (psSI->bSqlError)
				{
					Tboxp(psExt->px,psExt->py,psExt->px+psExt->lx-1,psExt->py+psExt->ly-1,sys.Color3DShadow,SET);
					if (psSI->pLastErrorText)
					{
						EH_AR arError;
						INT iRow;
						arError=ARCreate(psSI->pLastErrorText,"\n",&iRow);
						if (psExt->ncam<iRow) dispf(psExt->px+1,psExt->py+1,RGB(255,255,255),-1,STYLE_NORMAL,"SMALL F",3,arError[psExt->ncam]);
						ARDestroy(arError);
					}
				}
				else
				Tboxp(psExt->px,psExt->py,psExt->px+psExt->lx-1,psExt->py+psExt->ly-1,sys.Color3DLight,SET);
				break;
			 }

			 psExt->col1=GetSysColor(COLOR_MENUTEXT); 
			 psExt->col2=GetSysColor(COLOR_WINDOW);

			 if (psExt->bFocus) // selezione con il mouse
				{
					psExt->col1=GetSysColor(COLOR_HIGHLIGHTTEXT); 
					psExt->col2=ColorLum(GetSysColor(COLOR_HIGHLIGHT),30);
				} 

			 if (psExt->bSelected) // Selezionato fisso
				{
					psExt->col1=GetSysColor(COLOR_HIGHLIGHTTEXT); 
					psExt->col2=GetSysColor(COLOR_HIGHLIGHT); 
				} 

			Tboxp(psExt->px,psExt->py,psExt->px+psExt->lx-1,psExt->py+psExt->ly-2,psExt->col2,SET); //Sleep(100);

			psSI->rsSet->iCurrentRow=info;
			psSI->rsSet->iOffset=psSI->iSQLOffset;

			// Non ho ancora le linee da visualizzare
			if (psExt->ncam>=psSI->lRowsReady||
				(psSI->rsSet->iCurrentRow<psSI->iSQLOffset)||
				((psSI->rsSet->iCurrentRow-psSI->iSQLOffset)>=psSI->rsSet->iRowsLimit)) 
			{
				boxBrush(psExt->px,psExt->py,psExt->rClientArea.right,psExt->rClientArea.bottom,HS_VERTICAL,sys.Color3DLight,ColorLum(sys.Color3DHighLight,-10));
				Tline(psExt->px,psExt->rClientArea.bottom,psExt->rClientArea.right,psExt->rClientArea.bottom,sys.Color3DShadow,SET);
				break;
			}

			// RIchiedo stampa della riga
			psSI->funcNotify(	_adaptor(objCalled,WS_DISPLAY,info,psExt, psSI->rsSet));

			if (psSI->bDrawLineDiv) line(psExt->px,psExt->rClientArea.bottom,psExt->rClientArea.right,psExt->rClientArea.bottom,sys.colScrollDiv,SET);
			if (psExt->bFocus) 
			{
				boxFocus(psExt->px,psExt->py,psExt->px+psExt->lx-1,psExt->py+psExt->ly-2);
			}
			*/
			break;

	// --------------------------------------------------------------------------
	// SET della funzione esterna
	// --------------------------------------------------------------------------
	case WS_EXTNOTIFY: 
			 psSI->funcNotify=(LRESULT (*)(EH_NOTIFYPARAMS)) str;//(INT (*)(struct OBJ *,INT ,LONG  ,void  *str,EH_ODBC_RS )) str;
			 psSI->funcNotify(_adaptor(objCalled,WS_CREATE,0,NULL,NULL));
			 break;

	case WS_LINEVIEW: //	 
		psSI->ws.numcam=info;
		break;

	case WS_LINEEDIT: //	 
		psSI->ws.Enumcam=info;
		break;

	case WS_SIZE: break;
	case WS_MOVE: break;

	case WS_SETTITLE: break;
	case WS_CODENAME: 
		
		strAssign(&psSI->pszKeyCode,str); strTrim(psSI->pszKeyCode); 
		ARDestroy(psSI->arKeyCodeFld);
		psSI->arKeyCodeFld=ARCreate(psSI->pszKeyCode,"+",&psSI->iKeyCodePart);
		break;

	//
	// Riga in FOCUS
	//
		/*
	case WS_SET_ROWFOCUS: 
			if (!str) // Dal gestore oggetti
			{
				 if (info<0) {strAssign(&psSI->pCodeFocused,NULL); break;}
				 if (psSI->pCodeName&&psSI->rsSet)
				 {
					psSI->rsSet->iCurrentRow=info;
					psSI->rsSet->iOffset=psSI->ws.offset;

					// psSI->rsSet->iCurrentRow riga della query

					if (psSI->rsSet->iCurrentRow>=psSI->iSQLOffset&&
						psSI->rsSet->iCurrentRow<(psSI->iSQLOffset+psSI->lRowsReady))
					{
						strAssign(&psSI->pCodeFocused,sql_ptr(psSI->rsSet,psSI->pCodeName));
						strTrim(psSI->pCodeFocused);
					}
					else
					{
						strAssign(&psSI->pCodeFocused,NULL); // Non ho la selezione richiesta in memoria
					}
					dispxEx(0,80,"%d,%d = %s          ",
							psSI->rsSet->iCurrentRow,
							psSI->iSQLOffset+psSI->lRowsReady,
							psSI->pCodeFocused);
				 }
				return NULL;
			}
			else // Esterno
			{
				strAssign(&psSI->pCodeFocused,str);
				InvalidateRect(objCalled->hWnd,NULL,FALSE);
			}
			break;

	case WS_GET_ROWFOCUS: 
			 if (psSI->pCodeName&&psSI->pCodeFocused&&psSI->rsSet)
			 {
				CHAR *p;
				if (info<0) return NULL;
				psSI->rsSet->iCurrentRow=info;
				psSI->rsSet->iOffset=psSI->ws.offset;

				p=sql_ptr(psSI->rsSet,psSI->pCodeName); strTrimRight(p);
				if (!strcmp(p,psSI->pCodeFocused)) break;
			 }
			 return NULL;
*/

	//
	// Riga in SELECTED
	//
	case WS_SET_ROWSELECTED: 
			printf("qui");
		/*
			 if (!str) // Dal gestore oggetti
			 {
				 if (info<0) {strAssign(&psSI->pCodeSelected,NULL); InvalidateRect(objCalled->hWnd,NULL,FALSE); break;}
				 if (psSI->pszKeyCode&&psSI->rsSet)
				 {
					psSI->rsSet->iCurrentRow=info;
					psSI->rsSet->iOffset=psSI->ws.offset;
					_keyCodeBuilder(&psSI->pCodeSelected,psSI); //if (!strEmpty(p)) break;
				 }
				InvalidateRect(objCalled->hWnd,NULL,FALSE);
				return NULL;
			}
			else // Esterno
			{
				strAssign(&psSI->pCodeSelected,str);
				InvalidateRect(objCalled->hWnd,NULL,FALSE);
			}
			*/
			break;

	case WS_GET_ROWSELECTED: 

			//
			// Controllo di selezione
			// 
			if (psSI->pszKeyCode&&!strEmpty(psSI->pCodeSelected)&&psSI->rsSet)
			 {
				 CHAR * p;
				if (info<0) return NULL;

				//psSI->rsSet->iCurrent=info;
				p=_keyCodeBuilder(psSI,info); // Può ritornare Null in p se sto chiedendo una riga che non c'è (in fase di ingrandimento)
				if (!strCmp(p,psSI->pCodeSelected)) {ehFreeNN(p); break;}
				ehFreeNN(p); 
			 }
			 return NULL;

	case WS_EVENT:
		/*
			if (!psSI->rsSet) break;
			psSI->rsSet->iCurrentRow=info;
			psSI->rsSet->iOffset=psSI->iSQLOffset;
			if (psSI->funcNotify) 
			{
				BYTE *ptr=(BYTE *) (psSI->funcNotify)(_adaptor(objCalled,cmd,info,str,psSI->rsSet));
				return ptr;
			}
			*/
			printf("qui");
			break;

	case WS_BUF:
			break;

	default:
/*
		if (psSI->funcNotify) 
			(psSI->funcNotify)(_adaptor(objCalled,cmd,info,str,psSI->rsSet));
			else
			printf(__FUNCTION__ "Event ? [%d][%s]" CRLF,cmd,objCalled->nome); 
			*/
			break;
	}

	//PtScr=psSI->WinScr; 
	PtScr=NULL;
	if (!PtScr) PtScr=&rit;
	return PtScr;
}