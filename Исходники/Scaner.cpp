int TScaner::Scaner(TypeLex l) {
	int fl=0;
	int fl_len_const=0;
	int i; // текущая длина лексемы
	for (i=0;i<MAX_LEX;i++) l[i]=0; //очистили поле лексемы
	i=0; // лексема заполняется с позиции i

	start: // все игнорируемые элементы:
	while((t[uk]==' ') || (t[uk]=='\n') || (t[uk]=='\t')) {
		///////////////////////
		if (t[uk]=='\n'){
			if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}
			stroka++;
		}
		//////////////////////
		uk++;
	}
	// пропуск незначащих элементов
	if ( (t[uk]=='/') && (t[uk+1]=='/') )
	{ // начался комментарий, надо пропустить текст до "\n"
	uk=uk+2;
	while ( (t[uk]!='\n')/*&&(t[uk]!='\0')&&(t[uk]!='#')*/) uk++;
	///////////////////
		if (t[uk]=='\n'){

			if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}

		//stroka++;
		}
		//////////////////
	goto start;
	}
	
	// пропуск незначащих элементов
	if ( (t[uk]=='/') && (t[uk+1]=='*') )
	{ 
		uk=uk+2;////////////////////////////////////////////////////////////////
		// начался комментарий, надо пропустить текст до */
		while ( (t[uk]!='*')||(t[uk+1]!='/')) { 
			if(t[uk]=='#'||t[uk]=='\0') {fl=1; break;} 
			uk++; 
		} 
		if(fl){ 
			PrintError("Неоконченный комментарий",l); 
			return TError; 
		} 
		else{ uk=uk+2;} 
		goto start;
	}

	/*uk=uk+2;
	while ((t[uk]!='*')&&(t[uk+1]!='/')) 
		uk++;
	uk=uk+2;
	goto start;
	}*/


	if (t[uk]=='\0') {l[0]='#'; return TEnd;}
	
	if (Number)
	{
		l[i++]=t[uk++];
		while (Number)
			if (i<=MAX_CONST) l[i++]=t[uk++]; 
			else {uk++; fl_len_const=1;}
		if(!fl_len_const)
			return TConstInt10;
		else
		{PrintError("Длинная числовая константа",l);  
				return TError; }
	}
	else if(LetterBig||LetterSmall){
		//начинается идентификатор
		l[i++]=t[uk++];
		while(Number||LetterBig||LetterSmall)
			if (i<MAX_LEX-1) l[i++]=t[uk++]; else uk++;
		
		//длинный идентификатор обрезали
		int j; // проверка на ключевое слово
		for (j=0; j<MAX_KEYW; j++)
			if (strcmp(l,Keyword[j])==0) return IndexKeyword[j];
		return TIdent;
	}

	else if (t[uk]=='\'') { 
		uk++; // не будем включать кавычки константу 
		if (t[uk+1]!='\'') { 
			while( (t[uk]!='\'')&& (t[uk]!='\n')&& (t[uk]!='\0') && (t[uk]!='#') ){ 
				if (i<MAX_LEX-1) l[i++]=t[uk++]; 
				else uk++; // длинный идентификатор обрезали 
			} 
			/////////////////////
			if (t[uk]=='\n'){
				if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}
				//stroka++;
				//simvol=1;
			}
			///////////////////////
			if(t[uk]=='\'') 
				uk++; 
			PrintError("Неверная символьная константа",l);  
			return TError; 
		} 
		else { 
			if (t[uk]!='\n'&&t[uk]!='\0')
			{l[i++]=t[uk++]; 
			uk++; // закрывающая кавычка 
			return TConstSymvol; 
			}else { 
				//simvol=simvol-i+1;
				if(t[uk]=='\n'){

					if(i_mas==0){
						mass_str[i_mas++]=uk;
					}
					else{
						for(int j=0;j<i_mas;j++)
							if(mass_str[j]==uk){
								fl=1;
								break;
							}
							if(!fl){
								mass_str[i_mas++]=uk;
							}

					}

					//simvol=1;
					//stroka++;
				}
				//else {
					PrintError("Неверная символьная константа",l); 
					return TError; 
				}
		} 
	}

	/////////////////////////////////
	else if (t[uk]==',') { l[i++]=t[uk++]; return TZap; }
	else if (t[uk]==';') { l[i++]=t[uk++]; return TTochkaZap; }
	else if (t[uk]=='(') { l[i++]=t[uk++]; return TLSkob; }
	else if (t[uk]==')') { l[i++]=t[uk++]; return TRSkob; }
	else if (t[uk]=='{') { l[i++]=t[uk++]; return TLFigScob; }
	else if (t[uk]=='}') { l[i++]=t[uk++]; return TRFigScob; }
	else if (t[uk]=='[') { l[i++]=t[uk++]; return TLKvScob; }
	else if (t[uk]==']') { l[i++]=t[uk++]; return TRKvScob; }
	else if (t[uk]=='+') { l[i++]=t[uk++]; if (t[uk]=='+') { l[i++]=t[uk++]; return TPlusPlus; } return TPlus; }
	else if (t[uk]=='-') { l[i++]=t[uk++]; if (t[uk]=='-') { l[i++]=t[uk++]; return TMinusMinus; }return TMinus; }
	else if (t[uk]=='*') { l[i++]=t[uk++]; return TMul; }
	else if (t[uk]=='/') { l[i++]=t[uk++]; return TDiv; }
	else if (t[uk]=='%') { l[i++]=t[uk++]; return TMod; }
	else if (t[uk]=='<') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TMensheRavno; }return TMenshe; }
	else if (t[uk]=='>') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TBolsheRavno; }return TBolshe; }
	else if (t[uk]=='!') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TNeRavno ; }
	else { PrintError("Неверный символ",l); // ошибка 
	return TError;} }
	else if (t[uk]=='=') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TRavno; } else return TPris; }
	else { PrintError("Неверный символ",l); // ошибка
	//uk++;
	l[i++]=t[uk++]; //а то когда ошибку выводит, не выводит символ
	return TError;
	}
}