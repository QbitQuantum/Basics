bool CCLexicalAnalyzer::Create(const char *pStr)
{
	//strcpy(m_szOriginal, pStr);
	char seps[] = " ,\t'";	// ','는 임시로 빼 놓는다. ''로 스트링을 구분하기 위해
	char szToken[256];
	if(StrTok(szToken, pStr, seps)==false) return true;
	while(1){
		if(szToken[0]==' '){
		}
		else if(szToken[0]==','){
		}
		else if(szToken[0]=='\t'){
		}
		else if(szToken[0]=='\''){
			if(StrTok(szToken, NULL, "'")==false) return true;
			char *pAddToken = new char[strlen(szToken)+1];
			strcpy(pAddToken, szToken);
			m_Tokens.Add(pAddToken);
			if(StrTok(szToken, NULL, "'")==false) return true;
		}
		else{
			char *pAddToken = new char[strlen(szToken)+1];
			strcpy(pAddToken, szToken);
			m_Tokens.Add(pAddToken);
		}

		if(StrTok(szToken, NULL, seps)==false) return true;
	}
	/*
	char *pToken = strtok(pStr, seps);
	char szTemp[256];
	while(pToken!=NULL){
		if(pToken[0]=='\''){
			strcpy(szTemp, pToken);
			pToken = strtok(NULL, "'");
			strcpy(szTemp+strlen(szTemp), pToken);
			szTemp[strlen(szTemp)+1] = 0;
			szTemp[strlen(szTemp)] = '\'';
			pToken = szTemp;
		}
		char *pAddToken = new char[strlen(pToken)+1];
		strcpy(pAddToken, pToken);
		m_Tokens.Add(pAddToken);

		pToken = strtok(NULL, seps);
	}
	*/

	return true;
}