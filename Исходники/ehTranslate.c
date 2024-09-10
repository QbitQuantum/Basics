//
// ehTranslate()
//
UTF8 * ehTranslate(	ET_PARAM	enParam,
					UTF8 *		pszSource,
					CHAR *		pszLangSource,
					CHAR *		pszLangDest,
					CHAR *		pszJsonParams,	// {googlekey:"asda", bingkey:"asd"}
					ET_REPORT * psReport,
					void *		(* extAssist)(EN_MESSAGE enMess,LONG lParam,void *pVoid),
					EH_LST		lstBlackKey
					)

{
	WCHAR *pw;
	BYTE *pTradotto=NULL;
	S_PHRASES * psPh=NULL;
	S_PHSTR * psPhs;
	//INT f;
	BOOL bError=FALSE;
	INT iLen;
	INT iCharsBad;
	BYTE *pUtf;
	CHAR szLangDetect[20]="";
	double dRap;
	INT iWords;
	ET_REPORT sReportTemp;
	EH_JSON * psJson=NULL;
	CHAR * pszUserIp=NULL;
	INT		iMaxPhrases=0;
	ET_BLACK_ITEM sBlack;
	
	if (lstBlackKey) {
	
		if (lstBlackKey->iSize!=sizeof(ET_BLACK_ITEM)) ehExit("Usare transBlackListCreate();");
	}

	if (!_s.bReady) {_(_s); _s.bReady=true; ehAddExit(_transEndPoint);} // <-- Resetto la struttura Privata

	if (!psReport) psReport=&sReportTemp;
	memset(psReport,0,sizeof(ET_REPORT));

	if (!(enParam&ET_TRY_LOCAL)) extAssist=NULL;

	if (!pszLangSource) ehError();
	strcpy(psReport->szLangSource,pszLangSource);
	if (!pszLangDest) ehError();
	strcpy(psReport->szLangDest,pszLangDest);

	//
	// Assistente: ricerco prima in cache la frase completa
	//
	strTrim(pszSource);
	if (!*pszSource) {
		return strDup("");
	}

	if (enParam&ET_STAT) {
		psReport->dwChars=strlen(pszSource);
		psReport->dwWords=strWordCount(pszSource);
	}
	if (!(enParam&ET_TRANS)&&!(enParam&ET_LANGDETECT)) return NULL; // Nessun servizio richiesto

	if (pszJsonParams) {
		CHAR * psz;
		psJson=jsonCreate(pszJsonParams);
		psz=jsonGet(psJson,"maxPhrases");
		if (psz) iMaxPhrases=atoi(psz);
	}

	//
	// PREPARAZIONE FRASI DA RICHIEDERE
	// A seconda del servizio esterno di traduzione creo le frasi richieste
	//
	psPh=_phraseCreate(pszSource,iMaxPhrases);//,TTE_BING); 
	
	if (!psPh) {
		psReport->etError=GE_STRING_TOO_LONG;
		return NULL;
	}

	//
	// Richiesta traduzioni frasi
	//
	if (enParam&ET_OUTPUTDETT) {
		if (psPh->iPhraseToTrans>1) 
			printf("%s|%d}",pszLangDest,psPh->iPhraseToTrans);
			else
			printf("%s}",pszLangDest);
	}

	if (iMaxPhrases&&psPh->iPhraseToTrans>iMaxPhrases) {
	
		psReport->etError=GE_TOO_PHRASES;
		_phraseDestroy(psPh);
		jsonDestroy(psJson);
		return NULL;

	}
	if (enParam&ET_OUTPUTDETT) printf("|Phrase: total %d, problems %d, html:%d|" CRLF,psPh->iPhraseToTrans,psPh->iPhraseProblems,psPh->psTag->bHtml);
	if (enParam&ET_DOT_PROGRESS) printf("%d",psPh->iPhraseToTrans);

	//for (f=0;psPh->arPhrase[f];f++)
	for (lstLoop(psPh->lstPhrase,psPhs))
	{
		CHAR *	pszPhrase;
		CHAR *	pszPrefix=NULL;

		if (!psPhs->bTranslate) continue;

		// strTrim(psPhs->pszStr); 
		pszPhrase=psPhs->pszStr;
		if (strEmpty(pszPhrase)) continue;
		iLen=strlen(pszPhrase); if (iLen<2) continue; // Non traduco frasi con meno di 2 caratteri

		//
		// a. Controllo se è un numero
		//
 		if (!_isNaN(pszPhrase)) {ehFreePtr(&pszPrefix); continue;}

		//
		// b. Conto le parole
		//
		iWords=0; iCharsBad=0; dRap=0;
		if (enParam&ET_LANGDETECT) {

			iWords=strWordCount(pszPhrase);

			// Precontrollo stringa
			// Proporzione: iCharsBad:iLen=x:100
			iCharsBad=strCount(pszPhrase,".()[],-*_");
			dRap=iCharsBad*100/iLen;
			if (dRap>50) // Frase composta da oltre il 50% di simboli e non di lettere
			{
				psReport->etError=GE_STRING_SUSPECT; // L'indicazione della lingua sorgente è errata
				psPh->iPhraseProblems++;
				if (enParam&ET_OUTPUTDETT) printf("?");
				ehFreePtr(&pszPrefix); 
				continue;
			}
		}

		//
		// Local request ###########################################################################################
		//
		pUtf=NULL;

		if (extAssist) {

			S_TRANSLATION sTrans;

			sTrans.pszLangSource=pszLangSource;
			sTrans.pszLangDest=pszLangDest;
			sTrans.utfSource=pszPhrase;
			sTrans.utfDest=NULL;
			if (extAssist(WS_FIND,0,&sTrans)) {
				psReport->iLocalResponse++;
				if (enParam&ET_STAT) {
					psReport->dwLocalChars+=strlen(pszPhrase);
					psReport->dwLocalWords+=strWordCount(pszPhrase);
				}
				pUtf=sTrans.utfDest;
				if (pUtf) {
					psReport->enTech=ET_LOCAL;
					if (enParam&ET_SERVICE_CALL) printf("l$");
					if (enParam&ET_OUTPUTDETT) printf("l");
				}
			}
		}

		
		//
		// BING request ###########################################################################################
		//
		if (!pUtf&&
			psJson&&
			enParam&ET_TRY_BING) {
			
			CHAR * pszBingApp;
			INT iRequestDone=0;
			EH_LST lstKey;
			
			// Cerco Appi o multi Appid
			lstKey=lstNew();
			pszBingApp=jsonGet(psJson,"bingAppId");
			if (pszBingApp) lstPush(lstKey,pszBingApp);
			else {
			
				pszBingApp=jsonGet(psJson,"arBingAppId.length");
				if (pszBingApp) {
					INT a,iLen=atoi(pszBingApp);
					for (a=0;a<iLen;a++) {

						lstPush(lstKey,jsonGetf(psJson,"arBingAppId[%d]",a));

					}
				
				}
			}

			if (enParam&ET_OUTPUTDETT) printf("|pszBingApp:%s|" CRLF,pszBingApp);
			if (lstKey->iLength) {

				CHAR * pszAppId;
				if (enParam&ET_STAT) {

					psReport->dwBingChars+=strlen(pszPhrase);
					psReport->dwBingWords+=strWordCount(pszPhrase);

				}
				for (lstLoop(lstKey,pszAppId)) {

					if (_isBlackList(lstBlackKey,ET_BING,pszAppId)) continue;

					pUtf=_bingCall(		enParam,
										pszPhrase,
										pszLangSource,
										pszLangDest,
										pszAppId,
										&iRequestDone,
 										&psReport->etError); 

					if (enParam&ET_OUTPUTDETT) {
						printf("(%s) > (%s) #%d",pszPhrase,pUtf,psReport->etError);
					}
					psReport->iBingRequest+=iRequestDone;
					if (!strEmpty(pUtf)) 
						{	
							psReport->enTech=ET_BING;
							psReport->iBingResponse++; 
							if (enParam&ET_OUTPUTDETT) printf("B");
							break;
						}
						else
						{
							psReport->iBingErrors++; if (enParam&ET_OUTPUTDETT) printf("Bx");
							ehSleep(1000);
						}

					//
					// Abuso + BlackList
					//
					if (psReport->etError==GE_ABUSE&&
						lstBlackKey) {
					
							_(sBlack);
							sBlack.enTech=ET_BING;
							sBlack.pszAppId=strDup(pszAppId);
							lstPush(lstBlackKey,&sBlack);
					}
				}
			}
			lstDestroy(lstKey);
		}